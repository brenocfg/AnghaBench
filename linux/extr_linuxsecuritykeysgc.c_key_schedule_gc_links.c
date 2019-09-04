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
 int /*<<< orphan*/  KEY_GC_KEY_EXPIRED ; 
 int /*<<< orphan*/  key_gc_flags ; 
 int /*<<< orphan*/  key_gc_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void key_schedule_gc_links(void)
{
	set_bit(KEY_GC_KEY_EXPIRED, &key_gc_flags);
	schedule_work(&key_gc_work);
}