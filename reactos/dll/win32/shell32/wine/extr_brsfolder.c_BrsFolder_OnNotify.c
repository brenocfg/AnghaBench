#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  browse_info ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int code; scalar_t__ idFrom; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ NMTREEVIEWW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPNMTVDISPINFOW ;
typedef  scalar_t__ LPNMHDR ;

/* Variables and functions */
 int /*<<< orphan*/  BrsFolder_Treeview_Changed (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  BrsFolder_Treeview_Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  BrsFolder_Treeview_Expand (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  BrsFolder_Treeview_Rename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_BROWSE_FOR_FOLDER_TREEVIEW ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
#define  TVN_DELETEITEMA 135 
#define  TVN_DELETEITEMW 134 
#define  TVN_ENDLABELEDITA 133 
#define  TVN_ENDLABELEDITW 132 
#define  TVN_ITEMEXPANDINGA 131 
#define  TVN_ITEMEXPANDINGW 130 
#define  TVN_SELCHANGEDA 129 
#define  TVN_SELCHANGEDW 128 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static LRESULT BrsFolder_OnNotify( browse_info *info, UINT CtlID, LPNMHDR lpnmh )
{
    NMTREEVIEWW *pnmtv = (NMTREEVIEWW *)lpnmh;

    TRACE("%p %x %p msg=%x\n", info, CtlID, lpnmh, pnmtv->hdr.code);

    if (pnmtv->hdr.idFrom != IDC_BROWSE_FOR_FOLDER_TREEVIEW)
        return 0;

    switch (pnmtv->hdr.code)
    {
    case TVN_DELETEITEMA:
    case TVN_DELETEITEMW:
        return BrsFolder_Treeview_Delete( info, pnmtv );

    case TVN_ITEMEXPANDINGA:
    case TVN_ITEMEXPANDINGW:
        return BrsFolder_Treeview_Expand( info, pnmtv );

    case TVN_SELCHANGEDA:
    case TVN_SELCHANGEDW:
        return BrsFolder_Treeview_Changed( info, pnmtv );

    case TVN_ENDLABELEDITA:
    case TVN_ENDLABELEDITW:
        return BrsFolder_Treeview_Rename( info, (LPNMTVDISPINFOW)pnmtv );

    default:
        WARN("unhandled (%d)\n", pnmtv->hdr.code);
        break;
    }

    return 0;
}