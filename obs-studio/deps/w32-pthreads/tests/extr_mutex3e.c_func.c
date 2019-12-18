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
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mutex1 ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int washere ; 

void * func(void * arg)
{
  assert(pthread_mutex_trylock(&mutex1) == EBUSY);

  washere = 1;

  return 0; 
}