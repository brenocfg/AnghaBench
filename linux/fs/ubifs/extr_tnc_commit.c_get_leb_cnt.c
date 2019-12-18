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
struct ubifs_info {int leb_size; int ihead_offs; int max_idx_node_sz; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static int get_leb_cnt(struct ubifs_info *c, int cnt)
{
	int d;

	/* Assume maximum index node size (i.e. overestimate space needed) */
	cnt -= (c->leb_size - c->ihead_offs) / c->max_idx_node_sz;
	if (cnt < 0)
		cnt = 0;
	d = c->leb_size / c->max_idx_node_sz;
	return DIV_ROUND_UP(cnt, d);
}