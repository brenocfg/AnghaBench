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

/* Variables and functions */
 int /*<<< orphan*/  kasan_end_report (unsigned long*) ; 
 int /*<<< orphan*/  kasan_start_report (unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  print_address_description (void*) ; 
 int /*<<< orphan*/  print_shadow_for_address (void*) ; 

void kasan_report_invalid_free(void *object, unsigned long ip)
{
	unsigned long flags;

	kasan_start_report(&flags);
	pr_err("BUG: KASAN: double-free or invalid-free in %pS\n", (void *)ip);
	pr_err("\n");
	print_address_description(object);
	pr_err("\n");
	print_shadow_for_address(object);
	kasan_end_report(&flags);
}