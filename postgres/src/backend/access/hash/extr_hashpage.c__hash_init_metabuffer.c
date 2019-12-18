#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  double uint16 ;
struct TYPE_9__ {double hashm_ffactor; int hashm_bsize; int hashm_bmsize; int hashm_maxbucket; int hashm_highmask; int hashm_lowmask; int* hashm_spares; int* hashm_mapp; int hashm_ovflpoint; scalar_t__ hashm_firstfree; int /*<<< orphan*/  hashm_procid; scalar_t__ hashm_bmshift; scalar_t__ hashm_nmaps; scalar_t__ hashm_ntuples; int /*<<< orphan*/  hashm_version; int /*<<< orphan*/  hashm_magic; } ;
struct TYPE_8__ {int hasho_bucket; int /*<<< orphan*/  hasho_page_id; int /*<<< orphan*/  hasho_flag; void* hasho_nextblkno; void* hasho_prevblkno; } ;
struct TYPE_7__ {int pd_lower; } ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  int /*<<< orphan*/  HashMetaPageData ;
typedef  TYPE_3__* HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BMPG_MASK (TYPE_3__*) ; 
 int BMPG_SHIFT (TYPE_3__*) ; 
 scalar_t__ BYTE_TO_BIT ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASHO_PAGE_ID ; 
 int /*<<< orphan*/  HASH_MAGIC ; 
 int HASH_MAX_SPLITPOINTS ; 
 int /*<<< orphan*/  HASH_VERSION ; 
 int HashGetMaxBitmapSize (scalar_t__) ; 
 TYPE_3__* HashPageGetMeta (scalar_t__) ; 
 void* InvalidBlockNumber ; 
 int /*<<< orphan*/  LH_META_PAGE ; 
 int /*<<< orphan*/  MemSet (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int _hash_get_totalbuckets (int) ; 
 int _hash_log2 (int) ; 
 int /*<<< orphan*/  _hash_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 
 int _hash_spareindex (int) ; 

void
_hash_init_metabuffer(Buffer buf, double num_tuples, RegProcedure procid,
					  uint16 ffactor, bool initpage)
{
	HashMetaPage metap;
	HashPageOpaque pageopaque;
	Page		page;
	double		dnumbuckets;
	uint32		num_buckets;
	uint32		spare_index;
	uint32		i;

	/*
	 * Choose the number of initial bucket pages to match the fill factor
	 * given the estimated number of tuples.  We round up the result to the
	 * total number of buckets which has to be allocated before using its
	 * hashm_spares element. However always force at least 2 bucket pages. The
	 * upper limit is determined by considerations explained in
	 * _hash_expandtable().
	 */
	dnumbuckets = num_tuples / ffactor;
	if (dnumbuckets <= 2.0)
		num_buckets = 2;
	else if (dnumbuckets >= (double) 0x40000000)
		num_buckets = 0x40000000;
	else
		num_buckets = _hash_get_totalbuckets(_hash_spareindex(dnumbuckets));

	spare_index = _hash_spareindex(num_buckets);
	Assert(spare_index < HASH_MAX_SPLITPOINTS);

	page = BufferGetPage(buf);
	if (initpage)
		_hash_pageinit(page, BufferGetPageSize(buf));

	pageopaque = (HashPageOpaque) PageGetSpecialPointer(page);
	pageopaque->hasho_prevblkno = InvalidBlockNumber;
	pageopaque->hasho_nextblkno = InvalidBlockNumber;
	pageopaque->hasho_bucket = -1;
	pageopaque->hasho_flag = LH_META_PAGE;
	pageopaque->hasho_page_id = HASHO_PAGE_ID;

	metap = HashPageGetMeta(page);

	metap->hashm_magic = HASH_MAGIC;
	metap->hashm_version = HASH_VERSION;
	metap->hashm_ntuples = 0;
	metap->hashm_nmaps = 0;
	metap->hashm_ffactor = ffactor;
	metap->hashm_bsize = HashGetMaxBitmapSize(page);
	/* find largest bitmap array size that will fit in page size */
	for (i = _hash_log2(metap->hashm_bsize); i > 0; --i)
	{
		if ((1 << i) <= metap->hashm_bsize)
			break;
	}
	Assert(i > 0);
	metap->hashm_bmsize = 1 << i;
	metap->hashm_bmshift = i + BYTE_TO_BIT;
	Assert((1 << BMPG_SHIFT(metap)) == (BMPG_MASK(metap) + 1));

	/*
	 * Label the index with its primary hash support function's OID.  This is
	 * pretty useless for normal operation (in fact, hashm_procid is not used
	 * anywhere), but it might be handy for forensic purposes so we keep it.
	 */
	metap->hashm_procid = procid;

	/*
	 * We initialize the index with N buckets, 0 .. N-1, occupying physical
	 * blocks 1 to N.  The first freespace bitmap page is in block N+1.
	 */
	metap->hashm_maxbucket = num_buckets - 1;

	/*
	 * Set highmask as next immediate ((2 ^ x) - 1), which should be
	 * sufficient to cover num_buckets.
	 */
	metap->hashm_highmask = (1 << (_hash_log2(num_buckets + 1))) - 1;
	metap->hashm_lowmask = (metap->hashm_highmask >> 1);

	MemSet(metap->hashm_spares, 0, sizeof(metap->hashm_spares));
	MemSet(metap->hashm_mapp, 0, sizeof(metap->hashm_mapp));

	/* Set up mapping for one spare page after the initial splitpoints */
	metap->hashm_spares[spare_index] = 1;
	metap->hashm_ovflpoint = spare_index;
	metap->hashm_firstfree = 0;

	/*
	 * Set pd_lower just past the end of the metadata.  This is essential,
	 * because without doing so, metadata will be lost if xlog.c compresses
	 * the page.
	 */
	((PageHeader) page)->pd_lower =
		((char *) metap + sizeof(HashMetaPageData)) - (char *) page;
}