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
 unsigned long WORK_OFFQ_CANCELING ; 
 unsigned long WORK_OFFQ_POOL_SHIFT ; 
 int /*<<< orphan*/  WORK_STRUCT_PENDING ; 
 unsigned long get_work_pool_id (struct work_struct*) ; 
 int /*<<< orphan*/  set_work_data (struct work_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_work_canceling(struct work_struct *work)
{
	unsigned long pool_id = get_work_pool_id(work);

	pool_id <<= WORK_OFFQ_POOL_SHIFT;
	set_work_data(work, pool_id | WORK_OFFQ_CANCELING, WORK_STRUCT_PENDING);
}