#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_12__ {int /*<<< orphan*/  lcid; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
struct TYPE_14__ {int /*<<< orphan*/  time; } ;
struct TYPE_13__ {int wYear; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ DateInstance ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_LONGDATE ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_2__ create_systemtime (int /*<<< orphan*/ ) ; 
 TYPE_3__* date_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dateobj_to_string (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (int,char**) ; 
 int /*<<< orphan*/ * jsstr_nan () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_time (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  throw_type_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Date_toLocaleString(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    SYSTEMTIME st;
    DateInstance *date;
    jsstr_t *date_str;
    int date_len, time_len;

    TRACE("\n");

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    if(isnan(date->time)) {
        if(r)
            *r = jsval_string(jsstr_nan());
        return S_OK;
    }

    st = create_systemtime(local_time(date->time, date));

    if(st.wYear<1601 || st.wYear>9999)
        return dateobj_to_string(date, r);

    if(r) {
        WCHAR *ptr;

        date_len = GetDateFormatW(ctx->lcid, DATE_LONGDATE, &st, NULL, NULL, 0);
        time_len = GetTimeFormatW(ctx->lcid, 0, &st, NULL, NULL, 0);

        date_str = jsstr_alloc_buf(date_len+time_len-1, &ptr);
        if(!date_str)
            return E_OUTOFMEMORY;

        GetDateFormatW(ctx->lcid, DATE_LONGDATE, &st, NULL, ptr, date_len);
        GetTimeFormatW(ctx->lcid, 0, &st, NULL, ptr+date_len, time_len);
        ptr[date_len-1] = ' ';

        *r = jsval_string(date_str);
    }
    return S_OK;
}