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
struct work_struct {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned long WORK_OFFQ_CANCELING ; 
 unsigned long WORK_STRUCT_PWQ ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool work_is_canceling(struct work_struct *work)
{
	unsigned long data = atomic_long_read(&work->data);

	return !(data & WORK_STRUCT_PWQ) && (data & WORK_OFFQ_CANCELING);
}