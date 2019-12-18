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
struct dlm_plock_info {scalar_t__* version; } ;

/* Variables and functions */
 scalar_t__ DLM_PLOCK_VERSION_MAJOR ; 
 scalar_t__ DLM_PLOCK_VERSION_MINOR ; 
 int /*<<< orphan*/  DLM_PLOCK_VERSION_PATCH ; 
 int EINVAL ; 
 int /*<<< orphan*/  log_print (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int check_version(struct dlm_plock_info *info)
{
	if ((DLM_PLOCK_VERSION_MAJOR != info->version[0]) ||
	    (DLM_PLOCK_VERSION_MINOR < info->version[1])) {
		log_print("plock device version mismatch: "
			  "kernel (%u.%u.%u), user (%u.%u.%u)",
			  DLM_PLOCK_VERSION_MAJOR,
			  DLM_PLOCK_VERSION_MINOR,
			  DLM_PLOCK_VERSION_PATCH,
			  info->version[0],
			  info->version[1],
			  info->version[2]);
		return -EINVAL;
	}
	return 0;
}