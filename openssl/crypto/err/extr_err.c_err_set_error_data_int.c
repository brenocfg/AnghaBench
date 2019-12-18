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
 int /*<<< orphan*/  err_clear_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* err_get_state_int () ; 
 int /*<<< orphan*/  err_set_data (TYPE_1__*,int /*<<< orphan*/ ,char*,size_t,int) ; 

__attribute__((used)) static int err_set_error_data_int(char *data, size_t size, int flags,
                                  int deallocate)
{
    ERR_STATE *es;

    es = err_get_state_int();
    if (es == NULL)
        return 0;

    err_clear_data(es, es->top, deallocate);
    err_set_data(es, es->top, data, size, flags);

    return 1;
}