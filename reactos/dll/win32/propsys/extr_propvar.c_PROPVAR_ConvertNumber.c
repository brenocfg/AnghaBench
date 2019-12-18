#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONGLONG ;
struct TYPE_7__ {int QuadPart; } ;
struct TYPE_6__ {int QuadPart; } ;
struct TYPE_8__ {int cVal; int bVal; int iVal; int uiVal; int lVal; int ulVal; char* pszVal; int /*<<< orphan*/ * pwszVal; TYPE_2__ uhVal; TYPE_1__ hVal; } ;
struct TYPE_9__ {int vt; TYPE_3__ u; } ;
typedef  TYPE_4__* REFPROPVARIANT ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_TYPEMISMATCH ; 
 int /*<<< orphan*/  ERROR_ARITHMETIC_OVERFLOW ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
#define  VT_BSTR 139 
#define  VT_EMPTY 138 
#define  VT_I1 137 
#define  VT_I2 136 
#define  VT_I4 135 
#define  VT_I8 134 
#define  VT_LPSTR 133 
#define  VT_LPWSTR 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UI8 128 
 int _strtoi64 (char*,char**,int /*<<< orphan*/ ) ; 
 int strtolW (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT PROPVAR_ConvertNumber(REFPROPVARIANT pv, int dest_bits,
                                     BOOL dest_signed, LONGLONG *res)
{
    BOOL src_signed;

    switch (pv->vt)
    {
    case VT_I1:
        src_signed = TRUE;
        *res = pv->u.cVal;
        break;
    case VT_UI1:
        src_signed = FALSE;
        *res = pv->u.bVal;
        break;
    case VT_I2:
        src_signed = TRUE;
        *res = pv->u.iVal;
        break;
    case VT_UI2:
        src_signed = FALSE;
        *res = pv->u.uiVal;
        break;
    case VT_I4:
        src_signed = TRUE;
        *res = pv->u.lVal;
        break;
    case VT_UI4:
        src_signed = FALSE;
        *res = pv->u.ulVal;
        break;
    case VT_I8:
        src_signed = TRUE;
        *res = pv->u.hVal.QuadPart;
        break;
    case VT_UI8:
        src_signed = FALSE;
        *res = pv->u.uhVal.QuadPart;
        break;
    case VT_EMPTY:
        src_signed = FALSE;
        *res = 0;
        break;
    case VT_LPSTR:
    {
        char *end;
        *res = _strtoi64(pv->u.pszVal, &end, 0);
        if (pv->u.pszVal == end)
            return DISP_E_TYPEMISMATCH;
        src_signed = *res < 0;
        break;
    }
    case VT_LPWSTR:
    case VT_BSTR:
    {
        WCHAR *end;
        *res = strtolW(pv->u.pwszVal, &end, 0);
        if (pv->u.pwszVal == end)
            return DISP_E_TYPEMISMATCH;
        src_signed = *res < 0;
        break;
    }
    default:
        FIXME("unhandled vt %d\n", pv->vt);
        return E_NOTIMPL;
    }

    if (*res < 0 && src_signed != dest_signed)
        return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);

    if (dest_bits < 64)
    {
        if (dest_signed)
        {
            if (*res >= ((LONGLONG)1 << (dest_bits-1)) ||
                *res < ((LONGLONG)-1 << (dest_bits-1)))
                return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
        }
        else
        {
            if ((ULONGLONG)(*res) >= ((ULONGLONG)1 << dest_bits))
                return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
        }
    }

    return S_OK;
}