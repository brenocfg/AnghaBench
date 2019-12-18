#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  finishedEvent; int /*<<< orphan*/  startEvent; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ CLoopThread ;

/* Variables and functions */
 int /*<<< orphan*/  Event_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Close (int /*<<< orphan*/ *) ; 

void LoopThread_Close(CLoopThread *p)
{
  Thread_Close(&p->thread);
  Event_Close(&p->startEvent);
  Event_Close(&p->finishedEvent);
}