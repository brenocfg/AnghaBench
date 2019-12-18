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
typedef  int uint32_t ;
struct user_desc {int limit; scalar_t__ seg_32bit; scalar_t__ entry_number; scalar_t__ limit_in_pages; } ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  SYS_modify_ldt ; 
 int /*<<< orphan*/  SYS_set_thread_area ; 
 int /*<<< orphan*/  check_valid_segment (scalar_t__,int,int,int,int) ; 
 int errno ; 
 scalar_t__ gdt_entry_num ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int syscall (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool install_valid_mode(const struct user_desc *d, uint32_t ar,
			       bool oldmode, bool ldt)
{
	struct user_desc desc = *d;
	int ret;

	if (!ldt) {
#ifndef __i386__
		/* No point testing set_thread_area in a 64-bit build */
		return false;
#endif
		if (!gdt_entry_num)
			return false;
		desc.entry_number = gdt_entry_num;

		ret = syscall(SYS_set_thread_area, &desc);
	} else {
		ret = syscall(SYS_modify_ldt, oldmode ? 1 : 0x11,
			      &desc, sizeof(desc));

		if (ret < -1)
			errno = -ret;

		if (ret != 0 && errno == ENOSYS) {
			printf("[OK]\tmodify_ldt returned -ENOSYS\n");
			return false;
		}
	}

	if (ret == 0) {
		uint32_t limit = desc.limit;
		if (desc.limit_in_pages)
			limit = (limit << 12) + 4095;
		check_valid_segment(desc.entry_number, ldt, ar, limit, true);
		return true;
	} else {
		if (desc.seg_32bit) {
			printf("[FAIL]\tUnexpected %s failure %d\n",
			       ldt ? "modify_ldt" : "set_thread_area",
			       errno);
			nerrs++;
			return false;
		} else {
			printf("[OK]\t%s rejected 16 bit segment\n",
			       ldt ? "modify_ldt" : "set_thread_area");
			return false;
		}
	}
}