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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_self () ; 

int
main()
{
  assert(pthread_kill(pthread_self(), 1) == EINVAL);

  return 0;
}