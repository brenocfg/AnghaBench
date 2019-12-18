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
typedef  int /*<<< orphan*/  tid_t ;
typedef  int /*<<< orphan*/  func_info_t ;
struct TYPE_5__ {int func_cnt; TYPE_2__* funcs; } ;
typedef  TYPE_1__ dispex_data_t ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  tid; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_GetDocumentation (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* heap_realloc (TYPE_2__*,int) ; 

__attribute__((used)) static void add_func_info(dispex_data_t *data, DWORD *size, tid_t tid, DISPID id, ITypeInfo *dti)
{
    HRESULT hres;

    if(data->func_cnt && data->funcs[data->func_cnt-1].id == id)
        return;

    if(data->func_cnt == *size)
        data->funcs = heap_realloc(data->funcs, (*size <<= 1)*sizeof(func_info_t));

    hres = ITypeInfo_GetDocumentation(dti, id, &data->funcs[data->func_cnt].name, NULL, NULL, NULL);
    if(FAILED(hres))
        return;

    data->funcs[data->func_cnt].id = id;
    data->funcs[data->func_cnt].tid = tid;

    data->func_cnt++;
}