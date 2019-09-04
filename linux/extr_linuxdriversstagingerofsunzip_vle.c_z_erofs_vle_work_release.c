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
struct z_erofs_vle_workgroup {int dummy; } ;
struct z_erofs_vle_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __z_erofs_vle_work_release (struct z_erofs_vle_workgroup*,struct z_erofs_vle_work*) ; 
 struct z_erofs_vle_workgroup* z_erofs_vle_work_workgroup (struct z_erofs_vle_work*,int) ; 

void z_erofs_vle_work_release(struct z_erofs_vle_work *work)
{
	struct z_erofs_vle_workgroup *grp =
		z_erofs_vle_work_workgroup(work, true);

	__z_erofs_vle_work_release(grp, work);
}