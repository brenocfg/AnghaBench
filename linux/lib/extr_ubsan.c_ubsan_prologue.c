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
struct source_location {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_ubsan; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_source_location (char*,struct source_location*) ; 
 int /*<<< orphan*/  report_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ubsan_prologue(struct source_location *location,
			unsigned long *flags)
{
	current->in_ubsan++;
	spin_lock_irqsave(&report_lock, *flags);

	pr_err("========================================"
		"========================================\n");
	print_source_location("UBSAN: Undefined behaviour in", location);
}