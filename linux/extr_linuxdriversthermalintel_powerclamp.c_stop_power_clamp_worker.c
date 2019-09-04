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
struct powerclamp_worker_data {int clamping; int /*<<< orphan*/ * worker; int /*<<< orphan*/  cpu; int /*<<< orphan*/  idle_injection_work; int /*<<< orphan*/  balancing_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_clamping_mask ; 
 int /*<<< orphan*/  kthread_cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_destroy_worker (int /*<<< orphan*/ *) ; 
 struct powerclamp_worker_data* per_cpu_ptr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  worker_data ; 

__attribute__((used)) static void stop_power_clamp_worker(unsigned long cpu)
{
	struct powerclamp_worker_data *w_data = per_cpu_ptr(worker_data, cpu);

	if (!w_data->worker)
		return;

	w_data->clamping = false;
	/*
	 * Make sure that all works that get queued after this point see
	 * the clamping disabled. The counter part is not needed because
	 * there is an implicit memory barrier when the queued work
	 * is proceed.
	 */
	smp_wmb();
	kthread_cancel_work_sync(&w_data->balancing_work);
	kthread_cancel_delayed_work_sync(&w_data->idle_injection_work);
	/*
	 * The balancing work still might be queued here because
	 * the handling of the "clapming" variable, cancel, and queue
	 * operations are not synchronized via a lock. But it is not
	 * a big deal. The balancing work is fast and destroy kthread
	 * will wait for it.
	 */
	clear_bit(w_data->cpu, cpu_clamping_mask);
	kthread_destroy_worker(w_data->worker);

	w_data->worker = NULL;
}