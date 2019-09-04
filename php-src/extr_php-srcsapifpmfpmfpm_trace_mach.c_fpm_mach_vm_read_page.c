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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  fpm_pagesize ; 
 int /*<<< orphan*/  local_page ; 
 int /*<<< orphan*/  local_size ; 
 int /*<<< orphan*/  mach_error_string (scalar_t__) ; 
 scalar_t__ mach_vm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fpm_mach_vm_read_page(vm_offset_t page) /* {{{ */
{
	kern_return_t kr;

	kr = mach_vm_read(target, page, fpm_pagesize, &local_page, &local_size);
	if (kr != KERN_SUCCESS) {
		zlog(ZLOG_ERROR, "failed to read vm page: mach_vm_read(): %s (%d)", mach_error_string(kr), kr);
		return -1;
	}
	return 0;
}