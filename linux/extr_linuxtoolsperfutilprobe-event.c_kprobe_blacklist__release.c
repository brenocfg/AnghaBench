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
 int /*<<< orphan*/  kprobe_blacklist__delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kprobe_blacklist__release(void)
{
	kprobe_blacklist__delete(&kprobe_blacklist);
}