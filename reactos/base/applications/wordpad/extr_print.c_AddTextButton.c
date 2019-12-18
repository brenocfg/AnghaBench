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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int fMask; int fStyle; int cyChild; int cyMinChild; int cx; int cxMinChild; int cxIdeal; int /*<<< orphan*/  wID; int /*<<< orphan*/  hwndChild; int /*<<< orphan*/  cbSize; } ;
typedef  TYPE_1__ REBARBANDINFOW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_STRING_LEN ; 
 int RBBIM_CHILD ; 
 int RBBIM_CHILDSIZE ; 
 int RBBIM_ID ; 
 int RBBIM_IDEALSIZE ; 
 int RBBIM_SIZE ; 
 int RBBIM_STYLE ; 
 int RBBS_NOGRIPPER ; 
 int RBBS_VARIABLEHEIGHT ; 
 int /*<<< orphan*/  RB_INSERTBANDW ; 
 int /*<<< orphan*/  REBARBANDINFOW_V6_SIZE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULongToHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_BUTTONW ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 

__attribute__((used)) static void AddTextButton(HWND hRebarWnd, UINT string, UINT command, UINT id)
{
    REBARBANDINFOW rb;
    HINSTANCE hInstance = GetModuleHandleW(0);
    WCHAR text[MAX_STRING_LEN];
    HWND hButton;

    LoadStringW(hInstance, string, text, MAX_STRING_LEN);
    hButton = CreateWindowW(WC_BUTTONW, text,
                            WS_VISIBLE | WS_CHILD, 5, 5, 100, 15,
                            hRebarWnd, ULongToHandle(command), hInstance, NULL);

    rb.cbSize = REBARBANDINFOW_V6_SIZE;
    rb.fMask = RBBIM_SIZE | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_CHILD | RBBIM_IDEALSIZE | RBBIM_ID;
    rb.fStyle = RBBS_NOGRIPPER | RBBS_VARIABLEHEIGHT;
    rb.hwndChild = hButton;
    rb.cyChild = rb.cyMinChild = 22;
    rb.cx = rb.cxMinChild = 90;
    rb.cxIdeal = 100;
    rb.wID = id;

    SendMessageW(hRebarWnd, RB_INSERTBANDW, -1, (LPARAM)&rb);
}