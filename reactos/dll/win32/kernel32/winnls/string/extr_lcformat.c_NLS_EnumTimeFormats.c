#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* callbackex ) (char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* callback ) (char*) ;} ;
struct enumtimeformats_context {int flags; int type; int /*<<< orphan*/  lParam; TYPE_1__ u; scalar_t__ unicode; int /*<<< orphan*/  lcid; } ;
typedef  char WCHAR ;
typedef  int LCTYPE ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
#define  CALLBACK_ENUMPROC 130 
#define  CALLBACK_ENUMPROCEX 129 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ GetLocaleInfoA (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLocaleInfoW (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int LOCALE_SSHORTTIME ; 
 int LOCALE_STIMEFORMAT ; 
 int LOCALE_USE_CP_ACP ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
#define  TIME_NOSECONDS 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL NLS_EnumTimeFormats(struct enumtimeformats_context *ctxt)
{
    WCHAR bufW[256];
    char bufA[256];
    LCTYPE lctype;
    INT ret;

    if (!ctxt->u.callback)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    switch (ctxt->flags & ~LOCALE_USE_CP_ACP)
    {
    case 0:
        lctype = LOCALE_STIMEFORMAT;
        break;
    case TIME_NOSECONDS:
        lctype = LOCALE_SSHORTTIME;
        break;
    default:
        FIXME("Unknown time format (%d)\n", ctxt->flags);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    lctype |= ctxt->flags & LOCALE_USE_CP_ACP;
    if (ctxt->unicode)
        ret = GetLocaleInfoW(ctxt->lcid, lctype, bufW, ARRAY_SIZE(bufW));
    else
        ret = GetLocaleInfoA(ctxt->lcid, lctype, bufA, ARRAY_SIZE(bufA));

    if (ret)
    {
        switch (ctxt->type)
        {
        case CALLBACK_ENUMPROC:
            ctxt->u.callback(ctxt->unicode ? bufW : (WCHAR*)bufA);
            break;
        case CALLBACK_ENUMPROCEX:
            ctxt->u.callbackex(bufW, ctxt->lParam);
            break;
        default:
            ;
        }
    }

    return TRUE;
}