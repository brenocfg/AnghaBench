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
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
#define  KEXEC_INITRAMFS_CHECK 130 
#define  KEXEC_KERNEL_CHECK 129 
#define  MODULE_CHECK 128 

bool ima_hook_supports_modsig(enum ima_hooks func)
{
	switch (func) {
	case KEXEC_KERNEL_CHECK:
	case KEXEC_INITRAMFS_CHECK:
	case MODULE_CHECK:
		return true;
	default:
		return false;
	}
}