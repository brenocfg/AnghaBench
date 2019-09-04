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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  mutex1 ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int washere ; 

int
main()
{
  pthread_t t;

  assert(pthread_mutex_lock(&mutex1) == 0);

  assert(pthread_create(&t, NULL, func, NULL) == 0);
  assert(pthread_join(t, NULL) == 0);

  assert(pthread_mutex_unlock(&mutex1) == 0);

  assert(washere == 1);

  return 0;
}