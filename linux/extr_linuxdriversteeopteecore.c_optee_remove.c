#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct optee {TYPE_1__ call_queue; int /*<<< orphan*/  supp; int /*<<< orphan*/  wait_queue; scalar_t__ memremaped_shm; int /*<<< orphan*/  pool; int /*<<< orphan*/  teedev; int /*<<< orphan*/  supp_teedev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct optee*) ; 
 int /*<<< orphan*/  memunmap (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optee_disable_shm_cache (struct optee*) ; 
 int /*<<< orphan*/  optee_supp_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optee_wait_queue_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tee_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_shm_pool_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void optee_remove(struct optee *optee)
{
	/*
	 * Ask OP-TEE to free all cached shared memory objects to decrease
	 * reference counters and also avoid wild pointers in secure world
	 * into the old shared memory range.
	 */
	optee_disable_shm_cache(optee);

	/*
	 * The two devices has to be unregistered before we can free the
	 * other resources.
	 */
	tee_device_unregister(optee->supp_teedev);
	tee_device_unregister(optee->teedev);

	tee_shm_pool_free(optee->pool);
	if (optee->memremaped_shm)
		memunmap(optee->memremaped_shm);
	optee_wait_queue_exit(&optee->wait_queue);
	optee_supp_uninit(&optee->supp);
	mutex_destroy(&optee->call_queue.mutex);

	kfree(optee);
}