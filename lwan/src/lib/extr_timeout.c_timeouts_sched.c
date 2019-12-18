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
typedef  scalar_t__ timeout_t ;
struct timeouts {scalar_t__ curtime; int* pending; int /*<<< orphan*/  expired; int /*<<< orphan*/ ** wheel; } ;
struct timeout {int /*<<< orphan*/  tqe; int /*<<< orphan*/ * pending; scalar_t__ expires; } ;

/* Variables and functions */
 int WHEEL_C (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ timeout_rem (struct timeouts*,struct timeout*) ; 
 int timeout_slot (int,scalar_t__) ; 
 int timeout_wheel (scalar_t__) ; 
 int /*<<< orphan*/  timeouts_del (struct timeouts*,struct timeout*) ; 

__attribute__((used)) static void
timeouts_sched(struct timeouts *T, struct timeout *to, timeout_t expires)
{
    timeout_t rem;
    int wheel, slot;

    timeouts_del(T, to);

    to->expires = expires;

    if (expires > T->curtime) {
        rem = timeout_rem(T, to);

        /* rem is nonzero since:
         *   rem == timeout_rem(T,to),
         *       == to->expires - T->curtime
         *   and above we have expires > T->curtime.
         */
        wheel = timeout_wheel(rem);
        slot = timeout_slot(wheel, to->expires);

        to->pending = &T->wheel[wheel][slot];

        T->pending[wheel] |= WHEEL_C(1) << slot;
    } else {
        to->pending = &T->expired;
    }

    list_add_tail(to->pending, &to->tqe);
}