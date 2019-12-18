#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  err_clear (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_get_slot (TYPE_1__*) ; 
 TYPE_1__* err_get_state_int () ; 

void ERR_new(void)
{
    ERR_STATE *es;

    es = err_get_state_int();
    if (es == NULL)
        return;

    /* Allocate a slot */
    err_get_slot(es);
    err_clear(es, es->top, 0);
}