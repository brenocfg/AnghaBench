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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned long CONFIG_LSM_MMAP_MIN_ADDR ; 
 int /*<<< orphan*/  MEMPROTECT__MMAP_ZERO ; 
 int /*<<< orphan*/  SECCLASS_MEMPROTECT ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_mmap_addr(unsigned long addr)
{
	int rc = 0;

	if (addr < CONFIG_LSM_MMAP_MIN_ADDR) {
		u32 sid = current_sid();
		rc = avc_has_perm(&selinux_state,
				  sid, sid, SECCLASS_MEMPROTECT,
				  MEMPROTECT__MMAP_ZERO, NULL);
	}

	return rc;
}