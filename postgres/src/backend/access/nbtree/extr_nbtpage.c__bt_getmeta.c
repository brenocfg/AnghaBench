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
struct TYPE_4__ {scalar_t__ btm_magic; scalar_t__ btm_version; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BTPageOpaque ;
typedef  TYPE_1__ BTMetaPageData ;

/* Variables and functions */
 TYPE_1__* BTPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ BTREE_MAGIC ; 
 scalar_t__ BTREE_MIN_VERSION ; 
 scalar_t__ BTREE_VERSION ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  P_ISMETA (scalar_t__) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static BTMetaPageData *
_bt_getmeta(Relation rel, Buffer metabuf)
{
	Page		metapg;
	BTPageOpaque metaopaque;
	BTMetaPageData *metad;

	metapg = BufferGetPage(metabuf);
	metaopaque = (BTPageOpaque) PageGetSpecialPointer(metapg);
	metad = BTPageGetMeta(metapg);

	/* sanity-check the metapage */
	if (!P_ISMETA(metaopaque) ||
		metad->btm_magic != BTREE_MAGIC)
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("index \"%s\" is not a btree",
						RelationGetRelationName(rel))));

	if (metad->btm_version < BTREE_MIN_VERSION ||
		metad->btm_version > BTREE_VERSION)
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("version mismatch in index \"%s\": file version %d, "
						"current version %d, minimal supported version %d",
						RelationGetRelationName(rel),
						metad->btm_version, BTREE_VERSION, BTREE_MIN_VERSION)));

	return metad;
}