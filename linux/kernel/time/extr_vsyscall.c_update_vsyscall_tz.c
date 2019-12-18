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
struct vdso_data {int /*<<< orphan*/  tz_dsttime; int /*<<< orphan*/  tz_minuteswest; } ;
struct TYPE_2__ {int /*<<< orphan*/  tz_dsttime; int /*<<< orphan*/  tz_minuteswest; } ;

/* Variables and functions */
 size_t CS_HRES_COARSE ; 
 struct vdso_data* __arch_get_k_vdso_data () ; 
 int /*<<< orphan*/  __arch_sync_vdso_data (struct vdso_data*) ; 
 TYPE_1__ sys_tz ; 

void update_vsyscall_tz(void)
{
	struct vdso_data *vdata = __arch_get_k_vdso_data();

	vdata[CS_HRES_COARSE].tz_minuteswest = sys_tz.tz_minuteswest;
	vdata[CS_HRES_COARSE].tz_dsttime = sys_tz.tz_dsttime;

	__arch_sync_vdso_data(vdata);
}