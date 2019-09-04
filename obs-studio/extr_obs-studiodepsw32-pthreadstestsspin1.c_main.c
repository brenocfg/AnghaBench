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
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lock ; 
 scalar_t__ pthread_spin_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_unlock (int /*<<< orphan*/ *) ; 

int
main()
{
  assert(pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE) == 0);

  assert(pthread_spin_lock(&lock) == 0);

  assert(pthread_spin_unlock(&lock) == 0);

  assert(pthread_spin_destroy(&lock) == 0);

  assert(pthread_spin_lock(&lock) == EINVAL);

  return 0;
}