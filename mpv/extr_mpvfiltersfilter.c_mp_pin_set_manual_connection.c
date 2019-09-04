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
struct mp_pin {TYPE_2__* owner; } ;
struct TYPE_4__ {TYPE_1__* in; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_pin_set_manual_connection_for (struct mp_pin*,int /*<<< orphan*/ *) ; 

void mp_pin_set_manual_connection(struct mp_pin *p, bool connected)
{
    mp_pin_set_manual_connection_for(p, connected ? p->owner->in->parent : NULL);
}