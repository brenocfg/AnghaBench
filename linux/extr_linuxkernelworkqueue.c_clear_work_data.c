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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_STRUCT_NO_POOL ; 
 int /*<<< orphan*/  set_work_data (struct work_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void clear_work_data(struct work_struct *work)
{
	smp_wmb();	/* see set_work_pool_and_clear_pending() */
	set_work_data(work, WORK_STRUCT_NO_POOL, 0);
}