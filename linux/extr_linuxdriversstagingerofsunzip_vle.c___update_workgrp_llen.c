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
struct z_erofs_vle_workgroup {unsigned int llen; } ;

/* Variables and functions */
 unsigned int cmpxchg (unsigned int*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void __update_workgrp_llen(struct z_erofs_vle_workgroup *grp,
					 unsigned int llen)
{
	while (1) {
		unsigned int orig_llen = grp->llen;

		if (orig_llen >= llen || orig_llen ==
			cmpxchg(&grp->llen, orig_llen, llen))
			break;
	}
}