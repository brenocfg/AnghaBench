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
struct TYPE_2__ {int /*<<< orphan*/  temp_file_name; scalar_t__ found; } ;
struct vdso_info {TYPE_1__ vdso; } ;
struct machine {struct vdso_info* vdso_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct vdso_info**) ; 

void machine__exit_vdso(struct machine *machine)
{
	struct vdso_info *vdso_info = machine->vdso_info;

	if (!vdso_info)
		return;

	if (vdso_info->vdso.found)
		unlink(vdso_info->vdso.temp_file_name);
#if BITS_PER_LONG == 64
	if (vdso_info->vdso32.found)
		unlink(vdso_info->vdso32.temp_file_name);
	if (vdso_info->vdsox32.found)
		unlink(vdso_info->vdsox32.temp_file_name);
#endif

	zfree(&machine->vdso_info);
}