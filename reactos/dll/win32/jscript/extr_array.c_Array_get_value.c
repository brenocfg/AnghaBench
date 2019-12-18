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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ ArrayInstance ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_1__* array_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_separatorW ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Array_get_value(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t *r)
{
    ArrayInstance *array = array_from_jsdisp(jsthis);

    TRACE("\n");

    return array_join(ctx, &array->dispex, array->length, default_separatorW,
                      lstrlenW(default_separatorW), r);
}