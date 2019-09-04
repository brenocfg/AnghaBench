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
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  me ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main()
{
  pthread_t t;

  assert(pthread_create(&t, NULL, entry, NULL) == 0);

  Sleep(100);

  assert(pthread_equal(t, me) != 0);

  /* Success. */
  return 0;
}