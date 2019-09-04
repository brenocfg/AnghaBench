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
 int /*<<< orphan*/  kprobe_blacklist ; 
 scalar_t__ kprobe_blacklist__load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void kprobe_blacklist__init(void)
{
	if (!list_empty(&kprobe_blacklist))
		return;

	if (kprobe_blacklist__load(&kprobe_blacklist) < 0)
		pr_debug("No kprobe blacklist support, ignored\n");
}