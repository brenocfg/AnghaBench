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
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {int dummy; } ;
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_clock_sample (int /*<<< orphan*/  const,struct task_struct*) ; 
 int /*<<< orphan*/  cpu_clock_sample_group (int /*<<< orphan*/  const,struct task_struct*,int) ; 
 struct task_struct* get_task_for_clock_get (int /*<<< orphan*/  const) ; 
 struct timespec64 ns_to_timespec64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int posix_cpu_clock_get(const clockid_t clock, struct timespec64 *tp)
{
	const clockid_t clkid = CPUCLOCK_WHICH(clock);
	struct task_struct *tsk;
	u64 t;

	tsk = get_task_for_clock_get(clock);
	if (!tsk)
		return -EINVAL;

	if (CPUCLOCK_PERTHREAD(clock))
		t = cpu_clock_sample(clkid, tsk);
	else
		t = cpu_clock_sample_group(clkid, tsk, false);
	put_task_struct(tsk);

	*tp = ns_to_timespec64(t);
	return 0;
}