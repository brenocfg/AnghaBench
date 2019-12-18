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
typedef  int /*<<< orphan*/  button ;
struct TYPE_3__ {int iBitmap; int idCommand; int iString; scalar_t__ dwData; int /*<<< orphan*/  fsStyle; int /*<<< orphan*/  fsState; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  BTNS_BUTTON ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TB_ADDBUTTONSW ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static void AddButton(HWND hwndToolBar, int nImage, int nCommand)
{
    TBBUTTON button;

    ZeroMemory(&button, sizeof(button));
    button.iBitmap = nImage;
    button.idCommand = nCommand;
    button.fsState = TBSTATE_ENABLED;
    button.fsStyle = BTNS_BUTTON;
    button.dwData = 0;
    button.iString = -1;
    SendMessageW(hwndToolBar, TB_ADDBUTTONSW, 1, (LPARAM)&button);
}