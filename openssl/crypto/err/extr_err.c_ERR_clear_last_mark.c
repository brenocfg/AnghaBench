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
struct TYPE_3__ {int top; int bottom; int* err_flags; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 int ERR_FLAG_MARK ; 
 int ERR_NUM_ERRORS ; 
 TYPE_1__* err_get_state_int () ; 

int ERR_clear_last_mark(void)
{
    ERR_STATE *es;
    int top;

    es = err_get_state_int();
    if (es == NULL)
        return 0;

    top = es->top;
    while (es->bottom != top
           && (es->err_flags[top] & ERR_FLAG_MARK) == 0) {
        top = top > 0 ? top - 1 : ERR_NUM_ERRORS - 1;
    }

    if (es->bottom == top)
        return 0;
    es->err_flags[top] &= ~ERR_FLAG_MARK;
    return 1;
}