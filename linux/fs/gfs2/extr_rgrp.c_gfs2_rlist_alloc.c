#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gfs2_rgrp_list {unsigned int rl_rgrps; int /*<<< orphan*/ * rl_ghs; TYPE_1__** rl_rgd; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rd_gl; } ;

/* Variables and functions */
 int GFP_NOFS ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int) ; 

void gfs2_rlist_alloc(struct gfs2_rgrp_list *rlist)
{
	unsigned int x;

	rlist->rl_ghs = kmalloc_array(rlist->rl_rgrps,
				      sizeof(struct gfs2_holder),
				      GFP_NOFS | __GFP_NOFAIL);
	for (x = 0; x < rlist->rl_rgrps; x++)
		gfs2_holder_init(rlist->rl_rgd[x]->rd_gl,
				LM_ST_EXCLUSIVE, 0,
				&rlist->rl_ghs[x]);
}