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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/  const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
#define  LOCALE_SABBREVDAYNAME1 146 
#define  LOCALE_SABBREVDAYNAME2 145 
#define  LOCALE_SABBREVDAYNAME3 144 
#define  LOCALE_SABBREVDAYNAME4 143 
#define  LOCALE_SABBREVDAYNAME5 142 
#define  LOCALE_SABBREVDAYNAME6 141 
#define  LOCALE_SABBREVDAYNAME7 140 
#define  LOCALE_SABBREVMONTHNAME1 139 
#define  LOCALE_SABBREVMONTHNAME10 138 
#define  LOCALE_SABBREVMONTHNAME11 137 
#define  LOCALE_SABBREVMONTHNAME12 136 
#define  LOCALE_SABBREVMONTHNAME2 135 
#define  LOCALE_SABBREVMONTHNAME3 134 
#define  LOCALE_SABBREVMONTHNAME4 133 
#define  LOCALE_SABBREVMONTHNAME5 132 
#define  LOCALE_SABBREVMONTHNAME6 131 
#define  LOCALE_SABBREVMONTHNAME7 130 
#define  LOCALE_SABBREVMONTHNAME8 129 
#define  LOCALE_SABBREVMONTHNAME9 128 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int date_from_time (int /*<<< orphan*/ ) ; 
 TYPE_1__* date_this (int /*<<< orphan*/ *) ; 
 scalar_t__ hour_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_alloc (char*) ; 
 int /*<<< orphan*/ * jsstr_nan () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 scalar_t__ min_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ month_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ sec_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ week_day (int /*<<< orphan*/ ) ; 
 int year_from_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline HRESULT create_utc_string(script_ctx_t *ctx, vdisp_t *jsthis, jsval_t *r)
{
    static const WCHAR formatADW[] = { '%','s',',',' ','%','d',' ','%','s',' ','%','d',' ',
        '%','0','2','d',':','%','0','2','d',':','%','0','2','d',' ','U','T','C',0 };
    static const WCHAR formatBCW[] = { '%','s',',',' ','%','d',' ','%','s',' ','%','d',' ','B','.','C','.',' ',
        '%','0','2','d',':','%','0','2','d',':','%','0','2','d',' ','U','T','C',0 };

    static const DWORD week_ids[] = { LOCALE_SABBREVDAYNAME7, LOCALE_SABBREVDAYNAME1,
        LOCALE_SABBREVDAYNAME2, LOCALE_SABBREVDAYNAME3, LOCALE_SABBREVDAYNAME4,
        LOCALE_SABBREVDAYNAME5, LOCALE_SABBREVDAYNAME6 };
    static const DWORD month_ids[] = { LOCALE_SABBREVMONTHNAME1, LOCALE_SABBREVMONTHNAME2,
        LOCALE_SABBREVMONTHNAME3, LOCALE_SABBREVMONTHNAME4,
        LOCALE_SABBREVMONTHNAME5, LOCALE_SABBREVMONTHNAME6,
        LOCALE_SABBREVMONTHNAME7, LOCALE_SABBREVMONTHNAME8,
        LOCALE_SABBREVMONTHNAME9, LOCALE_SABBREVMONTHNAME10,
        LOCALE_SABBREVMONTHNAME11, LOCALE_SABBREVMONTHNAME12 };

    BOOL formatAD = TRUE;
    WCHAR week[64], month[64];
    WCHAR buf[192];
    DateInstance *date;
    jsstr_t *date_str;
    int year, day;
    DWORD lcid_en;

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    if(isnan(date->time)) {
        if(r)
            *r = jsval_string(jsstr_nan());
        return S_OK;
    }

    if(r) {
        lcid_en = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);

        week[0] = 0;
        GetLocaleInfoW(lcid_en, week_ids[(int)week_day(date->time)], week, ARRAY_SIZE(week));

        month[0] = 0;
        GetLocaleInfoW(lcid_en, month_ids[(int)month_from_time(date->time)], month, ARRAY_SIZE(month));

        year = year_from_time(date->time);
        if(year<0) {
            formatAD = FALSE;
            year = -year+1;
        }

        day = date_from_time(date->time);

        swprintf(buf, formatAD ? formatADW : formatBCW, week, day, month, year,
                (int)hour_from_time(date->time), (int)min_from_time(date->time),
                (int)sec_from_time(date->time));

        date_str = jsstr_alloc(buf);
        if(!date_str)
            return E_OUTOFMEMORY;

        *r = jsval_string(date_str);
    }
    return S_OK;
}