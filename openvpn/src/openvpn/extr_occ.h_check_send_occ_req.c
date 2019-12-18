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
struct TYPE_2__ {scalar_t__ occ_op; int /*<<< orphan*/  timeval; int /*<<< orphan*/  occ_interval; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETT_DEFAULT ; 
 int /*<<< orphan*/  TO_LINK_DEF (struct context*) ; 
 int /*<<< orphan*/  check_send_occ_req_dowork (struct context*) ; 
 scalar_t__ event_timeout_defined (int /*<<< orphan*/ *) ; 
 scalar_t__ event_timeout_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
check_send_occ_req(struct context *c)
{
    if (event_timeout_defined(&c->c2.occ_interval)
        && event_timeout_trigger(&c->c2.occ_interval,
                                 &c->c2.timeval,
                                 (!TO_LINK_DEF(c) && c->c2.occ_op < 0) ? ETT_DEFAULT : 0))
    {
        check_send_occ_req_dowork(c);
    }
}