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
struct timespec {long member_0; long member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_delay_np (struct timespec*) ; 

int
main(int argc, char * argv[])
{
  struct timespec interval = {1L, 500000000L};

  assert(pthread_delay_np(&interval) == 0);

  return 0;
}