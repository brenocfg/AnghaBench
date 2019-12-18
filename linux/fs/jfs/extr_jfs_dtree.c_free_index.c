#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tid_t ;
struct metapage {int dummy; } ;
struct inode {int dummy; } ;
struct dir_table_slot {int /*<<< orphan*/  addr2; scalar_t__ addr1; scalar_t__ slot; int /*<<< orphan*/  flag; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Dirtable ; 
 int /*<<< orphan*/  DIR_INDEX_FREE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct dir_table_slot* find_index (struct inode*,int /*<<< orphan*/ ,struct metapage**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_index (int /*<<< orphan*/ ,struct inode*,struct metapage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_metapage_dirty (struct metapage*) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 

__attribute__((used)) static void free_index(tid_t tid, struct inode *ip, u32 index, u32 next)
{
	struct dir_table_slot *dirtab_slot;
	s64 lblock;
	struct metapage *mp = NULL;

	dirtab_slot = find_index(ip, index, &mp, &lblock);

	if (!dirtab_slot)
		return;

	dirtab_slot->flag = DIR_INDEX_FREE;
	dirtab_slot->slot = dirtab_slot->addr1 = 0;
	dirtab_slot->addr2 = cpu_to_le32(next);

	if (mp) {
		lock_index(tid, ip, mp, index);
		mark_metapage_dirty(mp);
		release_metapage(mp);
	} else
		set_cflag(COMMIT_Dirtable, ip);
}