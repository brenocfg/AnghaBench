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
struct ubifs_info {int ileb_nxt; int ileb_cnt; int* ilebs; } ;

/* Variables and functions */
 int LPROPS_INDEX ; 
 int /*<<< orphan*/  LPROPS_NC ; 
 int LPROPS_TAKEN ; 
 int /*<<< orphan*/  dbg_cmt (char*,int) ; 
 int ubifs_change_one_lp (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int free_unused_idx_lebs(struct ubifs_info *c)
{
	int i, err = 0, lnum, er;

	for (i = c->ileb_nxt; i < c->ileb_cnt; i++) {
		lnum = c->ilebs[i];
		dbg_cmt("LEB %d", lnum);
		er = ubifs_change_one_lp(c, lnum, LPROPS_NC, LPROPS_NC, 0,
					 LPROPS_INDEX | LPROPS_TAKEN, 0);
		if (!err)
			err = er;
	}
	return err;
}