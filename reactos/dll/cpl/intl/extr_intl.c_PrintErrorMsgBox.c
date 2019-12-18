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

/* Variables and functions */
 int BUFFERSIZE ; 
 int /*<<< orphan*/  IDS_ERROR ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hApplet ; 

VOID
PrintErrorMsgBox(UINT msg)
{
    WCHAR szErrorText[BUFFERSIZE];
    WCHAR szErrorCaption[BUFFERSIZE];

    LoadStringW(hApplet, msg, szErrorText, sizeof(szErrorText) / sizeof(WCHAR));
    LoadStringW(hApplet, IDS_ERROR, szErrorCaption, sizeof(szErrorCaption) / sizeof(WCHAR));

    MessageBoxW(NULL, szErrorText, szErrorCaption, MB_OK | MB_ICONERROR);
}