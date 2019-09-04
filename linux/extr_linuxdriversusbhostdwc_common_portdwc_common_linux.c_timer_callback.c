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
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; int /*<<< orphan*/  lock; scalar_t__ scheduled; } ;
typedef  TYPE_1__ dwc_timer_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DEBUGC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t ; 
 TYPE_1__* timer ; 

__attribute__((used)) static void timer_callback(struct timer_list *tt)
{
	dwc_timer_t *timer = from_timer(timer, tt, t);
	dwc_irqflags_t flags;

	DWC_SPINLOCK_IRQSAVE(timer->lock, &flags);
	timer->scheduled = 0;
	DWC_SPINUNLOCK_IRQRESTORE(timer->lock, flags);
	DWC_DEBUGC("Timer %s callback", timer->name);
	timer->cb(timer->data);
}