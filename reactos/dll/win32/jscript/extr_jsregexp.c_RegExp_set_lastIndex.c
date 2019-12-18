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
struct TYPE_3__ {int /*<<< orphan*/  last_index; int /*<<< orphan*/  last_index_val; } ;
typedef  TYPE_1__ RegExpInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  index_from_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 TYPE_1__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT RegExp_set_lastIndex(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t value)
{
    RegExpInstance *regexp = regexp_from_jsdisp(jsthis);
    HRESULT hres;

    TRACE("\n");

    jsval_release(regexp->last_index_val);
    hres = jsval_copy(value, &regexp->last_index_val);
    if(FAILED(hres))
        return hres;

    regexp->last_index = index_from_val(ctx, value);
    return S_OK;
}