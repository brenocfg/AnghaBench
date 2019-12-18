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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {int /*<<< orphan*/  dispex; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ ArrayInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  alloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 

HRESULT create_array(script_ctx_t *ctx, DWORD length, jsdisp_t **ret)
{
    ArrayInstance *array;
    HRESULT hres;

    hres = alloc_array(ctx, NULL, &array);
    if(FAILED(hres))
        return hres;

    array->length = length;

    *ret = &array->dispex;
    return S_OK;
}