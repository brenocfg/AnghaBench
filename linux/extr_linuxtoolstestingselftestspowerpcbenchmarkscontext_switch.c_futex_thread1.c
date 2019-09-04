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
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int iterations ; 
 int /*<<< orphan*/  m1 ; 
 int /*<<< orphan*/  m2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigalrm_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *futex_thread1(void *arg)
{
	signal(SIGALRM, sigalrm_handler);
	alarm(1);

	while (1) {
		mutex_lock(m2);
		mutex_unlock(m1);

		iterations += 2;
	}

	return NULL;
}