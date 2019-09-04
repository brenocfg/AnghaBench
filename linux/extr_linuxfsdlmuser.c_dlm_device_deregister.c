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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dlm_ls {TYPE_1__ ls_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 

int dlm_device_deregister(struct dlm_ls *ls)
{
	/* The device is not registered.  This happens when the lockspace
	   was never used from userspace, or when device_create_lockspace()
	   calls dlm_release_lockspace() after the register fails. */
	if (!ls->ls_device.name)
		return 0;

	misc_deregister(&ls->ls_device);
	kfree(ls->ls_device.name);
	return 0;
}