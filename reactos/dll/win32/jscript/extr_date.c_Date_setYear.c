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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {double time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;
typedef  double DOUBLE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int /*<<< orphan*/  JS_E_MISSING_ARG ; 
 double NAN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  date_from_time (double) ; 
 TYPE_1__* date_this (int /*<<< orphan*/ *) ; 
 double floor (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  jsval_number (double) ; 
 double local_time (double,TYPE_1__*) ; 
 int /*<<< orphan*/  make_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_day (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  month_from_time (double) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double time_clip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_within_day (double) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  utc (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static HRESULT Date_setYear(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    DateInstance *date;
    DOUBLE t, year;
    HRESULT hres;

    TRACE("\n");

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    if(!argc)
        return throw_type_error(ctx, JS_E_MISSING_ARG, NULL);

    t = local_time(date->time, date);

    hres = to_number(ctx, argv[0], &year);
    if(FAILED(hres))
        return hres;

    if(isnan(year)) {
        date->time = year;
        if(r)
            *r = jsval_number(NAN);
        return S_OK;
    }

    year = year >= 0.0 ? floor(year) : -floor(-year);
    if(-1.0 < year && year < 100.0)
        year += 1900.0;

    date->time = time_clip(utc(make_date(make_day(year, month_from_time(t), date_from_time(t)), time_within_day(t)), date));

    if(r)
        *r = jsval_number(date->time);
    return S_OK;
}