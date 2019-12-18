#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int format; int grfFlags; int /*<<< orphan*/  IPropertyStorage_iface; int /*<<< orphan*/  locale; int /*<<< orphan*/  codePage; } ;
typedef  int /*<<< orphan*/  REFFMTID ;
typedef  TYPE_1__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IPropertyStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UNICODE ; 
 int /*<<< orphan*/  GetACP () ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int PROPSETFLAG_ANSI ; 
 int PROPSETFLAG_CASE_SENSITIVE ; 
 int /*<<< orphan*/  PropertyStorage_BaseConstruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT PropertyStorage_ConstructEmpty(IStream *stm,
 REFFMTID rfmtid, DWORD grfFlags, DWORD grfMode, IPropertyStorage** pps)
{
    PropertyStorage_impl *ps;
    HRESULT hr;

    assert(pps);
    hr = PropertyStorage_BaseConstruct(stm, rfmtid, grfMode, &ps);
    if (SUCCEEDED(hr))
    {
        ps->format = 0;
        ps->grfFlags = grfFlags;
        if (ps->grfFlags & PROPSETFLAG_CASE_SENSITIVE)
            ps->format = 1;
        /* default to Unicode unless told not to, as specified on msdn */
        if (ps->grfFlags & PROPSETFLAG_ANSI)
            ps->codePage = GetACP();
        else
            ps->codePage = CP_UNICODE;
        ps->locale = LOCALE_SYSTEM_DEFAULT;
        TRACE("Code page is %d, locale is %d\n", ps->codePage, ps->locale);
        *pps = &ps->IPropertyStorage_iface;
        TRACE("PropertyStorage %p constructed\n", ps);
        hr = S_OK;
    }
    return hr;
}