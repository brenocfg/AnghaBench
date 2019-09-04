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
 int /*<<< orphan*/  init_cond ; 
 int init_count ; 
 int /*<<< orphan*/  init_lock ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_for_thread_registration(int nthreads) {
    while (init_count < nthreads) {
        pthread_cond_wait(&init_cond, &init_lock);
    }
}