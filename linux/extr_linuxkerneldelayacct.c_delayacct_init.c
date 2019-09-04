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
 int /*<<< orphan*/  KMEM_CACHE (int /*<<< orphan*/ ,int) ; 
 int SLAB_ACCOUNT ; 
 int SLAB_PANIC ; 
 int /*<<< orphan*/  delayacct_cache ; 
 int /*<<< orphan*/  delayacct_tsk_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_task ; 
 int /*<<< orphan*/  task_delay_info ; 

void delayacct_init(void)
{
	delayacct_cache = KMEM_CACHE(task_delay_info, SLAB_PANIC|SLAB_ACCOUNT);
	delayacct_tsk_init(&init_task);
}