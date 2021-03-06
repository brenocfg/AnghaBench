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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_rwlock_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_rwlock_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rwlock ; 

int
main()
{
  assert(rwlock == NULL);

  assert(pthread_rwlock_init(&rwlock, NULL) == 0);

  assert(rwlock != NULL);

  assert(pthread_rwlock_destroy(&rwlock) == 0);

  assert(rwlock == NULL);

  return 0;
}