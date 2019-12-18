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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  make_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_day (double,double,double) ; 
 int /*<<< orphan*/  make_time (double,double,double,double) ; 
 double time_clip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT date_utc(script_ctx_t *ctx, unsigned argc, jsval_t *argv, double *ret)
{
    double year, month, vdate, hours, minutes, seconds, ms;
    HRESULT hres;

    TRACE("\n");

    if(argc) {
        hres = to_number(ctx, argv[0], &year);
        if(FAILED(hres))
            return hres;
        if(0 <= year && year <= 99)
            year += 1900;
    }else {
        year = 1900;
    }

    if(argc>1) {
        hres = to_number(ctx, argv[1], &month);
        if(FAILED(hres))
            return hres;
    }else {
        month = 0;
    }

    if(argc>2) {
        hres = to_number(ctx, argv[2], &vdate);
        if(FAILED(hres))
            return hres;
    }else {
        vdate = 1;
    }

    if(argc>3) {
        hres = to_number(ctx, argv[3], &hours);
        if(FAILED(hres))
            return hres;
    }else {
        hours = 0;
    }

    if(argc>4) {
        hres = to_number(ctx, argv[4], &minutes);
        if(FAILED(hres))
            return hres;
    }else {
        minutes = 0;
    }

    if(argc>5) {
        hres = to_number(ctx, argv[5], &seconds);
        if(FAILED(hres))
            return hres;
    }else {
        seconds = 0;
    }

    if(argc>6) {
        hres = to_number(ctx, argv[6], &ms);
        if(FAILED(hres))
            return hres;
    } else {
        ms = 0;
    }

    *ret = time_clip(make_date(make_day(year, month, vdate),
            make_time(hours, minutes,seconds, ms)));
    return S_OK;
}