#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwFlags; } ;
struct TYPE_7__ {int member_3; int member_4; int /*<<< orphan*/  cfFormat; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int cLinkTypes; int cPasteEntries; TYPE_4__* arrPasteEntries; int /*<<< orphan*/  lpSrcDataObj; int /*<<< orphan*/ * arrLinkTypes; } ;
typedef  TYPE_1__ OLEUIPASTESPECIALW ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ FORMATETC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PS_PASTELINK ; 
 int /*<<< orphan*/  IDC_PS_PASTELINKLIST ; 
 scalar_t__ IDataObject_QueryGetData (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int OLEUIPASTE_LINKANYTYPE ; 
 int PS_MAXLINKTYPES ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  add_entry_to_lb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static DWORD init_linklist(HWND hdlg, OLEUIPASTESPECIALW *ps)
{
    HRESULT hr;
    DWORD supported_mask = 0;
    DWORD items_added = 0;
    int link, req_fmt;
    FORMATETC fmt = {0, NULL, DVASPECT_CONTENT, -1, -1};

    for(link = 0; link < ps->cLinkTypes && link < PS_MAXLINKTYPES; link++)
    {
        fmt.cfFormat = ps->arrLinkTypes[link];
        hr = IDataObject_QueryGetData(ps->lpSrcDataObj, &fmt);
        if(hr == S_OK)
            supported_mask |= 1 << link;
    }
    TRACE("supported_mask %02x\n", supported_mask);
    for(req_fmt = 0; req_fmt < ps->cPasteEntries; req_fmt++)
    {
        DWORD linktypes;
        if(ps->arrPasteEntries[req_fmt].dwFlags & OLEUIPASTE_LINKANYTYPE)
            linktypes = 0xff;
        else
            linktypes = ps->arrPasteEntries[req_fmt].dwFlags & 0xff;

        if(linktypes & supported_mask)
        {
            add_entry_to_lb(hdlg, IDC_PS_PASTELINKLIST, ps->arrPasteEntries + req_fmt);
            items_added++;
        }
    }

    EnableWindow(GetDlgItem(hdlg, IDC_PS_PASTELINK), items_added != 0);
    return items_added;
}