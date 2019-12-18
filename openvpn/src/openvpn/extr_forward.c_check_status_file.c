#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timeval; } ;
struct TYPE_3__ {scalar_t__ status_output; } ;
struct context {TYPE_2__ c2; TYPE_1__ c1; } ;

/* Variables and functions */
 scalar_t__ status_trigger_tv (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
check_status_file(struct context *c)
{
    void check_status_file_dowork(struct context *c);

    if (c->c1.status_output)
    {
        if (status_trigger_tv(c->c1.status_output, &c->c2.timeval))
        {
            check_status_file_dowork(c);
        }
    }
}