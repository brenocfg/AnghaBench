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
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  func ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
main()
{
  pthread_t t1, t2;

  assert(pthread_create(&t1, NULL, func, (void *) 1) == 0);

  assert(pthread_create(&t2, NULL, func, (void *) 2) == 0);

  assert(pthread_equal(t1, t2) == 0);

  assert(pthread_equal(t1,t1) != 0);

  /* This is a hack. We don't want to rely on pthread_join
     yet if we can help it. */
   Sleep(4000);

  /* Success. */
  return 0;
}