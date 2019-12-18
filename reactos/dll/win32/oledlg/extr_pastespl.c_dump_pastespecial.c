#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ ULONG_PTR ;
typedef  size_t UINT ;
struct TYPE_7__ {int /*<<< orphan*/  tymed; int /*<<< orphan*/  lindex; int /*<<< orphan*/  dwAspect; int /*<<< orphan*/  ptd; int /*<<< orphan*/  cfFormat; } ;
struct TYPE_9__ {int /*<<< orphan*/  dwFlags; scalar_t__ lpstrResultText; scalar_t__ lpstrFormatName; TYPE_2__ fmtetc; } ;
struct TYPE_6__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_8__ {size_t cPasteEntries; size_t cLinkTypes; size_t cClsidExclude; int /*<<< orphan*/ * lpClsidExclude; int /*<<< orphan*/ * arrLinkTypes; TYPE_5__* arrPasteEntries; TYPE_1__ sizel; int /*<<< orphan*/  hMetaPict; int /*<<< orphan*/  fLink; int /*<<< orphan*/  nSelectedIndex; int /*<<< orphan*/  lpSrcDataObj; int /*<<< orphan*/  hResource; scalar_t__ lpszTemplate; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lCustData; int /*<<< orphan*/  lpfnHook; scalar_t__ lpszCaption; int /*<<< orphan*/  hWndOwner; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_3__ OLEUIPASTESPECIALW ;
typedef  size_t INT ;

/* Variables and functions */
 scalar_t__ IS_INTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,TYPE_5__*,...) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  dump_ps_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_pastespecial(const OLEUIPASTESPECIALW *ps)
{
    INT i;
    UINT j;

    dump_ps_flags(ps->dwFlags);
    TRACE("hwnd %p caption %s hook %p custdata %lx\n",
          ps->hWndOwner, debugstr_w(ps->lpszCaption), ps->lpfnHook, ps->lCustData);
    if(IS_INTRESOURCE(ps->lpszTemplate))
        TRACE("hinst %p template %04x hresource %p\n", ps->hInstance, (WORD)(ULONG_PTR)ps->lpszTemplate, ps->hResource);
    else
        TRACE("hinst %p template %s hresource %p\n", ps->hInstance, debugstr_w(ps->lpszTemplate), ps->hResource);
    TRACE("dataobj %p arrpasteent %p cpasteent %d arrlinktype %p clinktype %d\n",
          ps->lpSrcDataObj, ps->arrPasteEntries, ps->cPasteEntries,
          ps->arrLinkTypes, ps->cLinkTypes);
    TRACE("cclsidex %d lpclsidex %p nselect %d flink %d hmetapict %p size(%d,%d)\n",
          ps->cClsidExclude, ps->lpClsidExclude, ps->nSelectedIndex, ps->fLink,
          ps->hMetaPict, ps->sizel.cx, ps->sizel.cy);
    for(i = 0; i < ps->cPasteEntries; i++)
    {
        TRACE("arrPasteEntries[%d]: cFormat %08x pTargetDevice %p dwAspect %d lindex %d tymed %d\n",
              i, ps->arrPasteEntries[i].fmtetc.cfFormat, ps->arrPasteEntries[i].fmtetc.ptd,
              ps->arrPasteEntries[i].fmtetc.dwAspect, ps->arrPasteEntries[i].fmtetc.lindex,
              ps->arrPasteEntries[i].fmtetc.tymed);
        TRACE("\tformat name %s result text %s flags %04x\n", debugstr_w(ps->arrPasteEntries[i].lpstrFormatName),
              debugstr_w(ps->arrPasteEntries[i].lpstrResultText), ps->arrPasteEntries[i].dwFlags);
    }
    for(i = 0; i < ps->cLinkTypes; i++)
        TRACE("arrLinkTypes[%d] %08x\n", i, ps->arrLinkTypes[i]);
    for(j = 0; j < ps->cClsidExclude; j++)
        TRACE("lpClsidExclude[%u] %s\n", j, debugstr_guid(&ps->lpClsidExclude[j]));

}