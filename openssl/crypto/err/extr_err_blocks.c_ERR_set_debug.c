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
struct TYPE_4__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 TYPE_1__* err_get_state_int () ; 
 int /*<<< orphan*/  err_set_debug (TYPE_1__*,int /*<<< orphan*/ ,char const*,int,char const*) ; 

void ERR_set_debug(const char *file, int line, const char *func)
{
    ERR_STATE *es;

    es = err_get_state_int();
    if (es == NULL)
        return;

    err_set_debug(es, es->top, file, line, func);
}