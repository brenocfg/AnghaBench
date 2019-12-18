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
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hwndListBox; } ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 int const CB_GETDROPPEDSTATE ; 
 int const CB_GETEXTENDEDUI ; 
 int const CB_SETEXTENDEDUI ; 
 int const CB_SHOWDROPDOWN ; 
 int FALSE ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int TRUE ; 
 scalar_t__ VK_DOWN ; 
 int VK_F4 ; 
 scalar_t__ VK_UP ; 
#define  WM_KEYDOWN 129 
#define  WM_SYSKEYDOWN 128 

__attribute__((used)) static BOOL EDIT_CheckCombo(EDITSTATE *es, UINT msg, INT key)
{
    HWND hLBox = es->hwndListBox;
    HWND hCombo;
    BOOL bDropped;
    int  nEUI;

    if (!hLBox)
        return FALSE;

    hCombo   = GetParent(es->hwndSelf);
    bDropped = TRUE;
    nEUI     = 0;

    TRACE("[%p]: handling msg %x (%x)\n", es->hwndSelf, msg, key);

    if (key == VK_UP || key == VK_DOWN)
    {
        if (SendMessageW(hCombo, CB_GETEXTENDEDUI, 0, 0))
            nEUI = 1;

        if (msg == WM_KEYDOWN || nEUI)
            bDropped = (BOOL)SendMessageW(hCombo, CB_GETDROPPEDSTATE, 0, 0);
    }

    switch (msg)
    {
    case WM_KEYDOWN:
        if (!bDropped && nEUI && (key == VK_UP || key == VK_DOWN))
        {
            /* make sure ComboLBox pops up */
            SendMessageW(hCombo, CB_SETEXTENDEDUI, FALSE, 0);
            key = VK_F4;
            nEUI = 2;
        }

        SendMessageW(hLBox, WM_KEYDOWN, key, 0);
        break;

    case WM_SYSKEYDOWN: /* Handle Alt+up/down arrows */
        if (nEUI)
           SendMessageW(hCombo, CB_SHOWDROPDOWN, !bDropped, 0);
        else
           SendMessageW(hLBox, WM_KEYDOWN, VK_F4, 0);
        break;
    }

    if (nEUI == 2)
        SendMessageW(hCombo, CB_SETEXTENDEDUI, TRUE, 0);

    return TRUE;
}