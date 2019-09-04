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
struct TYPE_3__ {int top; int* err_flags; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FLAG_CLEAR ; 
 TYPE_1__* ERR_get_state () ; 
 int /*<<< orphan*/  constant_time_eq_int (int,int /*<<< orphan*/ ) ; 
 int constant_time_select_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void err_clear_last_constant_time(int clear)
{
    ERR_STATE *es;
    int top;

    es = ERR_get_state();
    if (es == NULL)
        return;

    top = es->top;

    /*
     * Flag error as cleared but remove it elsewhere to avoid two errors
     * accessing the same error stack location, revealing timing information.
     */
    clear = constant_time_select_int(constant_time_eq_int(clear, 0),
                                     0, ERR_FLAG_CLEAR);
    es->err_flags[top] |= clear;
}