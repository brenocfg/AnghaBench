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
struct kasan_access_info {int /*<<< orphan*/  first_bad_addr; scalar_t__ access_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_has_shadow (struct kasan_access_info*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kasan_end_report (unsigned long*) ; 
 int /*<<< orphan*/  kasan_start_report (unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_address_description (void*) ; 
 int /*<<< orphan*/  print_error_description (struct kasan_access_info*) ; 
 int /*<<< orphan*/  print_shadow_for_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kasan_report_error(struct kasan_access_info *info)
{
	unsigned long flags;

	kasan_start_report(&flags);

	print_error_description(info);
	pr_err("\n");

	if (!addr_has_shadow(info)) {
		dump_stack();
	} else {
		print_address_description((void *)info->access_addr);
		pr_err("\n");
		print_shadow_for_address(info->first_bad_addr);
	}

	kasan_end_report(&flags);
}