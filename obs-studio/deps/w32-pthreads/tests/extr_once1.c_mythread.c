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
 int /*<<< orphan*/  myfunc ; 
 int /*<<< orphan*/  once ; 
 scalar_t__ pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *
mythread(void * arg)
{
   assert(pthread_once(&once, myfunc) == 0);

   return 0;
}