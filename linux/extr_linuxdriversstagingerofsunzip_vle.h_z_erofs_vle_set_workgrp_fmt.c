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
struct z_erofs_vle_workgroup {unsigned int flags; } ;

/* Variables and functions */
 unsigned int Z_EROFS_VLE_WORKGRP_FMT_MASK ; 

__attribute__((used)) static inline void z_erofs_vle_set_workgrp_fmt(
	struct z_erofs_vle_workgroup *grp,
	unsigned int fmt)
{
	grp->flags = fmt | (grp->flags & ~Z_EROFS_VLE_WORKGRP_FMT_MASK);
}