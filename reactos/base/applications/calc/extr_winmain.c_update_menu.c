#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ usesep; } ;
struct TYPE_4__ {scalar_t__* sel; scalar_t__ idc; int /*<<< orphan*/  idm; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  BST_UNCHECKED ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDM_VIEW_GROUP ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int MF_UNCHECKED ; 
 unsigned int SIZEOF (TYPE_1__*) ; 
 TYPE_2__ calc ; 
 TYPE_1__* upd ; 

__attribute__((used)) static void update_menu(HWND hWnd)
{
    HMENU        hMenu = GetSubMenu(GetMenu(hWnd), 1);
    unsigned int x;

    for (x=0; x<SIZEOF(upd); x++) {
        if (*(upd[x].sel) != upd[x].idc) {
            CheckMenuItem(hMenu, upd[x].idm, MF_BYCOMMAND|MF_UNCHECKED);
            CheckDlgButton(hWnd, upd[x].idc, BST_UNCHECKED);
        } else {
            CheckMenuItem(hMenu, upd[x].idm, MF_BYCOMMAND|MF_CHECKED);
            CheckDlgButton(hWnd, upd[x].idc, BST_CHECKED);
        }
    }
    CheckMenuItem(hMenu, IDM_VIEW_GROUP, MF_BYCOMMAND|(calc.usesep ? MF_CHECKED : MF_UNCHECKED));
}