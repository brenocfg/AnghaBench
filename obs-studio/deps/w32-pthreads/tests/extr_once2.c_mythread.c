#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  myfunc ; 
 TYPE_1__ numThreads ; 
 int /*<<< orphan*/ * once ; 
 scalar_t__ pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *
mythread(void * arg)
{
   assert(pthread_once(&once[(int)(size_t)arg], myfunc) == 0);
   EnterCriticalSection(&numThreads.cs);
   numThreads.i++;   
   LeaveCriticalSection(&numThreads.cs);
   return (void*)(size_t)0;
}