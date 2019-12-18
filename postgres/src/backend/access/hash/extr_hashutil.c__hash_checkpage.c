#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hashm_magic; scalar_t__ hashm_version; } ;
struct TYPE_4__ {int hasho_flag; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  HashPageOpaqueData ;
typedef  TYPE_1__* HashPageOpaque ;
typedef  TYPE_2__* HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HASH_MAGIC ; 
 scalar_t__ HASH_VERSION ; 
 TYPE_2__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 int LH_META_PAGE ; 
 scalar_t__ MAXALIGN (int) ; 
 int /*<<< orphan*/  PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialSize (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 

void
_hash_checkpage(Relation rel, Buffer buf, int flags)
{
	Page		page = BufferGetPage(buf);

	/*
	 * ReadBuffer verifies that every newly-read page passes
	 * PageHeaderIsValid, which means it either contains a reasonably sane
	 * page header or is all-zero.  We have to defend against the all-zero
	 * case, however.
	 */
	if (PageIsNew(page))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("index \"%s\" contains unexpected zero page at block %u",
						RelationGetRelationName(rel),
						BufferGetBlockNumber(buf)),
				 errhint("Please REINDEX it.")));

	/*
	 * Additionally check that the special area looks sane.
	 */
	if (PageGetSpecialSize(page) != MAXALIGN(sizeof(HashPageOpaqueData)))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("index \"%s\" contains corrupted page at block %u",
						RelationGetRelationName(rel),
						BufferGetBlockNumber(buf)),
				 errhint("Please REINDEX it.")));

	if (flags)
	{
		HashPageOpaque opaque = (HashPageOpaque) PageGetSpecialPointer(page);

		if ((opaque->hasho_flag & flags) == 0)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("index \"%s\" contains corrupted page at block %u",
							RelationGetRelationName(rel),
							BufferGetBlockNumber(buf)),
					 errhint("Please REINDEX it.")));
	}

	/*
	 * When checking the metapage, also verify magic number and version.
	 */
	if (flags == LH_META_PAGE)
	{
		HashMetaPage metap = HashPageGetMeta(page);

		if (metap->hashm_magic != HASH_MAGIC)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("index \"%s\" is not a hash index",
							RelationGetRelationName(rel))));

		if (metap->hashm_version != HASH_VERSION)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("index \"%s\" has wrong hash version",
							RelationGetRelationName(rel)),
					 errhint("Please REINDEX it.")));
	}
}