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
struct dlm_plock_info {int /*<<< orphan*/ * version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_PLOCK_VERSION_MAJOR ; 
 int /*<<< orphan*/  DLM_PLOCK_VERSION_MINOR ; 
 int /*<<< orphan*/  DLM_PLOCK_VERSION_PATCH ; 

__attribute__((used)) static inline void set_version(struct dlm_plock_info *info)
{
	info->version[0] = DLM_PLOCK_VERSION_MAJOR;
	info->version[1] = DLM_PLOCK_VERSION_MINOR;
	info->version[2] = DLM_PLOCK_VERSION_PATCH;
}