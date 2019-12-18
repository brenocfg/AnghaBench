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
typedef  int /*<<< orphan*/  szErrorText ;
typedef  int /*<<< orphan*/  szErrorCaption ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int BUFFERSIZE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID
ResourceMessageBox(
    HINSTANCE hInstance,
    HWND hwnd,
    UINT uType,
    UINT uCaptionId,
    UINT uMessageId)
{
    WCHAR szErrorText[BUFFERSIZE];
    WCHAR szErrorCaption[BUFFERSIZE];

    LoadStringW(hInstance, uMessageId, szErrorText, sizeof(szErrorText) / sizeof(WCHAR));
    LoadStringW(hInstance, uCaptionId, szErrorCaption, sizeof(szErrorCaption) / sizeof(WCHAR));

    MessageBoxW(hwnd, szErrorText, szErrorCaption, uType);
}