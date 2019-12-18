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
struct vo_internal {int need_wakeup; int /*<<< orphan*/  wakeup; } ;
struct vo {TYPE_1__* driver; struct vo_internal* in; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wakeup ) (struct vo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vo*) ; 

__attribute__((used)) static void wakeup_locked(struct vo *vo)
{
    struct vo_internal *in = vo->in;

    pthread_cond_broadcast(&in->wakeup);
    if (vo->driver->wakeup)
        vo->driver->wakeup(vo);
    in->need_wakeup = true;
}