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
struct TYPE_4__ {size_t bottom; size_t top; int* err_flags; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 int ERR_FLAG_MARK ; 
 int ERR_NUM_ERRORS ; 
 int /*<<< orphan*/  err_clear (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* err_get_state_int () ; 

int ERR_pop_to_mark(void)
{
    ERR_STATE *es;

    es = err_get_state_int();
    if (es == NULL)
        return 0;

    while (es->bottom != es->top
           && (es->err_flags[es->top] & ERR_FLAG_MARK) == 0) {
        err_clear(es, es->top, 0);
        es->top = es->top > 0 ? es->top - 1 : ERR_NUM_ERRORS - 1;
    }

    if (es->bottom == es->top)
        return 0;
    es->err_flags[es->top] &= ~ERR_FLAG_MARK;
    return 1;
}