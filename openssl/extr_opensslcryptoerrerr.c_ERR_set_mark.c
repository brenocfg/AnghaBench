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
struct TYPE_3__ {size_t bottom; size_t top; int /*<<< orphan*/ * err_flags; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FLAG_MARK ; 
 TYPE_1__* ERR_get_state () ; 

int ERR_set_mark(void)
{
    ERR_STATE *es;

    es = ERR_get_state();
    if (es == NULL)
        return 0;

    if (es->bottom == es->top)
        return 0;
    es->err_flags[es->top] |= ERR_FLAG_MARK;
    return 1;
}