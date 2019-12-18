#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DateConstr_info ; 
 int /*<<< orphan*/  DateConstr_value ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONSTR ; 
 int /*<<< orphan*/  create_builtin_constructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_date (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

HRESULT create_date_constr(script_ctx_t *ctx, jsdisp_t *object_prototype, jsdisp_t **ret)
{
    jsdisp_t *date;
    HRESULT hres;

    static const WCHAR DateW[] = {'D','a','t','e',0};

    hres = create_date(ctx, object_prototype, 0.0, &date);
    if(FAILED(hres))
        return hres;

    hres = create_builtin_constructor(ctx, DateConstr_value, DateW, &DateConstr_info,
            PROPF_CONSTR|7, date, ret);

    jsdisp_release(date);
    return hres;
}