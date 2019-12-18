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
 int bankAccount ; 
 scalar_t__ pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock1 ; 

void * rdfunc(void * arg)
{
  int ba;

  assert(pthread_rwlock_rdlock(&rwlock1) == 0);
  ba = bankAccount;
  assert(pthread_rwlock_unlock(&rwlock1) == 0);

  return ((void *)(size_t)ba);
}