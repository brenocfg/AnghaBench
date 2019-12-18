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
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 

int
main(int argc, char * argv[])
{
  pthread_t id;
  void* result = (void*)0;

  /* Create a single thread and wait for it to exit. */
  assert(pthread_create(&id, NULL, func, (void *) 123) == 0);

  assert(pthread_join(id, &result) == 0);

  assert((int)(size_t)result == 123);

  /* Success. */
  return 0;
}