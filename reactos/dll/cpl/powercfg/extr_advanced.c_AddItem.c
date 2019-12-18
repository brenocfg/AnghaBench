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
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ POWER_ACTION ;
typedef  size_t LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 size_t CB_ERR ; 
 int /*<<< orphan*/  CB_INSERTSTRING ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 size_t SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
AddItem(HWND hDlgCtrl, INT ResourceId, LPARAM lParam, POWER_ACTION * lpAction)
{
    TCHAR szBuffer[MAX_PATH];
    LRESULT Index;

    if (LoadString(hApplet, ResourceId, szBuffer, MAX_PATH) < MAX_PATH)
    {
        Index = SendMessage(hDlgCtrl, CB_INSERTSTRING, -1, (LPARAM)szBuffer);
        if (Index != CB_ERR)
        {
            SendMessage(hDlgCtrl, CB_SETITEMDATA, (WPARAM)Index, lParam);
            lpAction[Index] = (POWER_ACTION)lParam;
        }
    }
}