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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin ; 
 int /*<<< orphan*/  unlocker ; 
 int wasHere ; 

int
main()
{
  pthread_t t;

  wasHere = 0;
  assert(pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE) == 0);
  assert(pthread_spin_lock(&spin) == 0);
  assert(pthread_create(&t, NULL, unlocker, (void*)0) == 0);
  assert(pthread_join(t, NULL) == 0);
  /*
   * Our spinlocks don't record the owner thread so any thread can unlock the spinlock,
   * but nor is it an error for any thread to unlock a spinlock that is not locked.
   */
  assert(pthread_spin_unlock(&spin) == 0);
  assert(pthread_spin_destroy(&spin) == 0);
  assert(wasHere == 2);

  return 0;
}