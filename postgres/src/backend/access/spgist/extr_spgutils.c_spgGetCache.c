#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ leafType; scalar_t__ prefixType; scalar_t__ labelType; scalar_t__ attType; } ;
typedef  TYPE_1__ spgConfigIn ;
struct TYPE_21__ {scalar_t__ atttypid; } ;
struct TYPE_20__ {int /*<<< orphan*/ * rd_amcache; int /*<<< orphan*/ * rd_indcollation; TYPE_10__* rd_att; int /*<<< orphan*/  rd_indexcxt; } ;
struct TYPE_19__ {int /*<<< orphan*/  lastUsedPages; TYPE_1__ config; int /*<<< orphan*/  attLabelType; int /*<<< orphan*/  attPrefixType; int /*<<< orphan*/  attType; int /*<<< orphan*/  attLeafType; } ;
struct TYPE_18__ {scalar_t__ magicNumber; int /*<<< orphan*/  lastUsedPages; } ;
struct TYPE_16__ {int natts; } ;
typedef  TYPE_2__ SpGistMetaPageData ;
typedef  TYPE_3__ SpGistCache ;
typedef  TYPE_4__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  ReadBuffer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_4__*) ; 
 int /*<<< orphan*/  SPGIST_COMPRESS_PROC ; 
 int /*<<< orphan*/  SPGIST_CONFIG_PROC ; 
 scalar_t__ SPGIST_MAGIC_NUMBER ; 
 int /*<<< orphan*/  SPGIST_METAPAGE_BLKNO ; 
 TYPE_2__* SpGistPageGetMeta (int /*<<< orphan*/ ) ; 
 TYPE_9__* TupleDescAttr (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  fillTypeDesc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ index_getprocid (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

SpGistCache *
spgGetCache(Relation index)
{
	SpGistCache *cache;

	if (index->rd_amcache == NULL)
	{
		Oid			atttype;
		spgConfigIn in;
		FmgrInfo   *procinfo;
		Buffer		metabuffer;
		SpGistMetaPageData *metadata;

		cache = MemoryContextAllocZero(index->rd_indexcxt,
									   sizeof(SpGistCache));

		/* SPGiST doesn't support multi-column indexes */
		Assert(index->rd_att->natts == 1);

		/*
		 * Get the actual data type of the indexed column from the index
		 * tupdesc.  We pass this to the opclass config function so that
		 * polymorphic opclasses are possible.
		 */
		atttype = TupleDescAttr(index->rd_att, 0)->atttypid;

		/* Call the config function to get config info for the opclass */
		in.attType = atttype;

		procinfo = index_getprocinfo(index, 1, SPGIST_CONFIG_PROC);
		FunctionCall2Coll(procinfo,
						  index->rd_indcollation[0],
						  PointerGetDatum(&in),
						  PointerGetDatum(&cache->config));

		/* Get the information we need about each relevant datatype */
		fillTypeDesc(&cache->attType, atttype);

		if (OidIsValid(cache->config.leafType) &&
			cache->config.leafType != atttype)
		{
			if (!OidIsValid(index_getprocid(index, 1, SPGIST_COMPRESS_PROC)))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("compress method must be defined when leaf type is different from input type")));

			fillTypeDesc(&cache->attLeafType, cache->config.leafType);
		}
		else
		{
			cache->attLeafType = cache->attType;
		}

		fillTypeDesc(&cache->attPrefixType, cache->config.prefixType);
		fillTypeDesc(&cache->attLabelType, cache->config.labelType);

		/* Last, get the lastUsedPages data from the metapage */
		metabuffer = ReadBuffer(index, SPGIST_METAPAGE_BLKNO);
		LockBuffer(metabuffer, BUFFER_LOCK_SHARE);

		metadata = SpGistPageGetMeta(BufferGetPage(metabuffer));

		if (metadata->magicNumber != SPGIST_MAGIC_NUMBER)
			elog(ERROR, "index \"%s\" is not an SP-GiST index",
				 RelationGetRelationName(index));

		cache->lastUsedPages = metadata->lastUsedPages;

		UnlockReleaseBuffer(metabuffer);

		index->rd_amcache = (void *) cache;
	}
	else
	{
		/* assume it's up to date */
		cache = (SpGistCache *) index->rd_amcache;
	}

	return cache;
}