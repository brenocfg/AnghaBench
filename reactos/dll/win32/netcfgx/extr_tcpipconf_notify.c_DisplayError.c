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
typedef  int /*<<< orphan*/  szTitle ;
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netcfgx_hInstance ; 

VOID
DisplayError(UINT ResTxt, UINT ResTitle, UINT Type)
{
    WCHAR szBuffer[300];
    WCHAR szTitle[100];

    if (LoadStringW(netcfgx_hInstance, ResTxt, szBuffer, sizeof(szBuffer)/sizeof(WCHAR)))
        szBuffer[(sizeof(szBuffer)/sizeof(WCHAR))-1] = L'\0';
    else
        szBuffer[0] = L'\0';

    if (LoadStringW(netcfgx_hInstance, ResTitle, szTitle, sizeof(szTitle)/sizeof(WCHAR)))
        szTitle[(sizeof(szTitle)/sizeof(WCHAR))-1] = L'\0';
    else
        szTitle[0] = L'\0';

    MessageBoxW(NULL, szBuffer, szTitle, Type);
}