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
 int /*<<< orphan*/  dup_mmap_sem ; 
 int /*<<< orphan*/  percpu_down_read (int /*<<< orphan*/ *) ; 

void uprobe_start_dup_mmap(void)
{
	percpu_down_read(&dup_mmap_sem);
}