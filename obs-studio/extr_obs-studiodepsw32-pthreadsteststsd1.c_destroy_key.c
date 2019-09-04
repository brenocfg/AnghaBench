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
 int* accesscount ; 
 int /*<<< orphan*/  assert (int) ; 
 int* thread_destroyed ; 

__attribute__((used)) static void
destroy_key(void * arg)
{
  int * j = (int *) arg;

  (*j)++;

  assert(*j == 2);

  thread_destroyed[j - accesscount] = 1;
}