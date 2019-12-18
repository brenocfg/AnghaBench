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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int MAXLONGLONG ; 
 int NAN ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 scalar_t__ iswdigit (char const) ; 
 scalar_t__ iswspace (char const) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int pow (int,int) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const**) ; 

__attribute__((used)) static HRESULT JSGlobal_parseFloat(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    LONGLONG d = 0, hlp;
    jsstr_t *val_str;
    int exp = 0;
    const WCHAR *str;
    BOOL ret_nan = TRUE, positive = TRUE;
    HRESULT hres;

    if(!argc) {
        if(r)
            *r = jsval_number(NAN);
        return S_OK;
    }

    hres = to_flat_string(ctx, argv[0], &val_str, &str);
    if(FAILED(hres))
        return hres;

    while(iswspace(*str)) str++;

    if(*str == '+')
        str++;
    else if(*str == '-') {
        positive = FALSE;
        str++;
    }

    if(iswdigit(*str))
        ret_nan = FALSE;

    while(iswdigit(*str)) {
        hlp = d*10 + *(str++) - '0';
        if(d>MAXLONGLONG/10 || hlp<0) {
            exp++;
            break;
        }
        else
            d = hlp;
    }
    while(iswdigit(*str)) {
        exp++;
        str++;
    }

    if(*str == '.') str++;

    if(iswdigit(*str))
        ret_nan = FALSE;

    while(iswdigit(*str)) {
        hlp = d*10 + *(str++) - '0';
        if(d>MAXLONGLONG/10 || hlp<0)
            break;

        d = hlp;
        exp--;
    }
    while(iswdigit(*str))
        str++;

    if(*str && !ret_nan && (*str=='e' || *str=='E')) {
        int sign = 1, e = 0;

        str++;
        if(*str == '+')
            str++;
        else if(*str == '-') {
            sign = -1;
            str++;
        }

        while(iswdigit(*str)) {
            if(e>INT_MAX/10 || (e = e*10 + *str++ - '0')<0)
                e = INT_MAX;
        }
        e *= sign;

        if(exp<0 && e<0 && exp+e>0) exp = INT_MIN;
        else if(exp>0 && e>0 && exp+e<0) exp = INT_MAX;
        else exp += e;
    }

    jsstr_release(val_str);

    if(ret_nan) {
        if(r)
            *r = jsval_number(NAN);
        return S_OK;
    }

    if(!positive)
        d = -d;
    if(r)
        *r = jsval_number(exp>0 ? d*pow(10, exp) : d/pow(10, -exp));
    return S_OK;
}