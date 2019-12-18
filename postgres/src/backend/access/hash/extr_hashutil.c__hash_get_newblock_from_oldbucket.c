#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hashm_maxbucket; int /*<<< orphan*/  hashm_lowmask; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_TO_BLKNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_METAPAGE ; 
 int /*<<< orphan*/  HASH_READ ; 
 TYPE_1__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LH_META_PAGE ; 
 int /*<<< orphan*/  _hash_get_newbucket_from_oldbucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BlockNumber
_hash_get_newblock_from_oldbucket(Relation rel, Bucket old_bucket)
{
	Bucket		new_bucket;
	Buffer		metabuf;
	HashMetaPage metap;
	BlockNumber blkno;

	metabuf = _hash_getbuf(rel, HASH_METAPAGE, HASH_READ, LH_META_PAGE);
	metap = HashPageGetMeta(BufferGetPage(metabuf));

	new_bucket = _hash_get_newbucket_from_oldbucket(rel, old_bucket,
													metap->hashm_lowmask,
													metap->hashm_maxbucket);
	blkno = BUCKET_TO_BLKNO(metap, new_bucket);

	_hash_relbuf(rel, metabuf);

	return blkno;
}