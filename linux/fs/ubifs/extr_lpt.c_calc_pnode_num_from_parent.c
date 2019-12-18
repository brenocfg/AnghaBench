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
struct ubifs_nnode {int num; } ;
struct ubifs_info {int lpt_hght; } ;

/* Variables and functions */
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_FANOUT_SHIFT ; 

__attribute__((used)) static int calc_pnode_num_from_parent(const struct ubifs_info *c,
				      struct ubifs_nnode *parent, int iip)
{
	int i, n = c->lpt_hght - 1, pnum = parent->num, num = 0;

	for (i = 0; i < n; i++) {
		num <<= UBIFS_LPT_FANOUT_SHIFT;
		num |= pnum & (UBIFS_LPT_FANOUT - 1);
		pnum >>= UBIFS_LPT_FANOUT_SHIFT;
	}
	num <<= UBIFS_LPT_FANOUT_SHIFT;
	num |= iip;
	return num;
}