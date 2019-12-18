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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 struct task_struct* __get_task_for_clock (int /*<<< orphan*/  const,int,int) ; 

__attribute__((used)) static inline struct task_struct *get_task_for_clock(const clockid_t clock)
{
	return __get_task_for_clock(clock, true, false);
}