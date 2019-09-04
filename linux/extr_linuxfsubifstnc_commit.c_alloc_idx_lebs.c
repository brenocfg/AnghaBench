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
struct ubifs_info {int* ilebs; scalar_t__ ileb_cnt; scalar_t__ ileb_nxt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dbg_cmt (char*,int) ; 
 scalar_t__ dbg_is_chk_index (struct ubifs_info*) ; 
 int get_leb_cnt (struct ubifs_info*,int) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int prandom_u32 () ; 
 int ubifs_find_free_leb_for_idx (struct ubifs_info*) ; 

__attribute__((used)) static int alloc_idx_lebs(struct ubifs_info *c, int cnt)
{
	int i, leb_cnt, lnum;

	c->ileb_cnt = 0;
	c->ileb_nxt = 0;
	leb_cnt = get_leb_cnt(c, cnt);
	dbg_cmt("need about %d empty LEBS for TNC commit", leb_cnt);
	if (!leb_cnt)
		return 0;
	c->ilebs = kmalloc_array(leb_cnt, sizeof(int), GFP_NOFS);
	if (!c->ilebs)
		return -ENOMEM;
	for (i = 0; i < leb_cnt; i++) {
		lnum = ubifs_find_free_leb_for_idx(c);
		if (lnum < 0)
			return lnum;
		c->ilebs[c->ileb_cnt++] = lnum;
		dbg_cmt("LEB %d", lnum);
	}
	if (dbg_is_chk_index(c) && !(prandom_u32() & 7))
		return -ENOSPC;
	return 0;
}