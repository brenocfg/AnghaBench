#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WRes ;
struct TYPE_4__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  finishedEvent; int /*<<< orphan*/  startEvent; scalar_t__ stop; } ;
typedef  TYPE_1__ CLoopThread ;

/* Variables and functions */
 int /*<<< orphan*/  AutoResetEvent_CreateNotSignaled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoopThreadFunc ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Thread_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

WRes LoopThread_Create(CLoopThread *p)
{
  p->stop = 0;
  RINOK(AutoResetEvent_CreateNotSignaled(&p->startEvent));
  RINOK(AutoResetEvent_CreateNotSignaled(&p->finishedEvent));
  return Thread_Create(&p->thread, LoopThreadFunc, p);
}