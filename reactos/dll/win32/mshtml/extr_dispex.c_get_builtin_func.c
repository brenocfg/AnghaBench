#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ id; } ;
typedef  TYPE_1__ func_info_t ;
struct TYPE_6__ {int func_cnt; TYPE_1__* funcs; } ;
typedef  TYPE_2__ dispex_data_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 

__attribute__((used)) static HRESULT get_builtin_func(dispex_data_t *data, DISPID id, func_info_t **ret)
{
    int min, max, n;

    min = 0;
    max = data->func_cnt-1;

    while(min <= max) {
        n = (min+max)/2;

        if(data->funcs[n].id == id) {
            *ret = data->funcs+n;
            return S_OK;
        }

        if(data->funcs[n].id < id)
            min = n+1;
        else
            max = n-1;
    }

    WARN("invalid id %x\n", id);
    return DISP_E_UNKNOWNNAME;
}