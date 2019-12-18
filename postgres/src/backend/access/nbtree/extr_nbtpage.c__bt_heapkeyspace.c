#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_10__ {scalar_t__ btm_root; scalar_t__ btm_version; scalar_t__ btm_magic; scalar_t__ btm_fastroot; } ;
struct TYPE_9__ {int /*<<< orphan*/ * rd_amcache; int /*<<< orphan*/  rd_indexcxt; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_2__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BTREE_MAGIC ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 scalar_t__ BTREE_MIN_VERSION ; 
 scalar_t__ BTREE_NOVAC_VERSION ; 
 scalar_t__ BTREE_VERSION ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/ * MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ P_NONE ; 
 int /*<<< orphan*/  _bt_getbuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* _bt_getmeta (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

bool
_bt_heapkeyspace(Relation rel)
{
	BTMetaPageData *metad;

	if (rel->rd_amcache == NULL)
	{
		Buffer		metabuf;

		metabuf = _bt_getbuf(rel, BTREE_METAPAGE, BT_READ);
		metad = _bt_getmeta(rel, metabuf);

		/*
		 * If there's no root page yet, _bt_getroot() doesn't expect a cache
		 * to be made, so just stop here.  (XXX perhaps _bt_getroot() should
		 * be changed to allow this case.)
		 */
		if (metad->btm_root == P_NONE)
		{
			uint32		btm_version = metad->btm_version;

			_bt_relbuf(rel, metabuf);
			return btm_version > BTREE_NOVAC_VERSION;
		}

		/*
		 * Cache the metapage data for next time
		 *
		 * An on-the-fly version upgrade performed by _bt_upgrademetapage()
		 * can change the nbtree version for an index without invalidating any
		 * local cache.  This is okay because it can only happen when moving
		 * from version 2 to version 3, both of which are !heapkeyspace
		 * versions.
		 */
		rel->rd_amcache = MemoryContextAlloc(rel->rd_indexcxt,
											 sizeof(BTMetaPageData));
		memcpy(rel->rd_amcache, metad, sizeof(BTMetaPageData));
		_bt_relbuf(rel, metabuf);
	}

	/* Get cached page */
	metad = (BTMetaPageData *) rel->rd_amcache;
	/* We shouldn't have cached it if any of these fail */
	Assert(metad->btm_magic == BTREE_MAGIC);
	Assert(metad->btm_version >= BTREE_MIN_VERSION);
	Assert(metad->btm_version <= BTREE_VERSION);
	Assert(metad->btm_fastroot != P_NONE);

	return metad->btm_version > BTREE_NOVAC_VERSION;
}