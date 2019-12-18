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
struct TYPE_3__ {int /*<<< orphan*/  status_hwnd; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ InternetExplorer ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_SETTEXTW ; 
 int /*<<< orphan*/  SB_SIMPLEID ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT update_ie_statustext(InternetExplorer* This, LPCWSTR text)
{
    if(!SendMessageW(This->status_hwnd, SB_SETTEXTW, MAKEWORD(SB_SIMPLEID, 0), (LPARAM)text))
        return E_FAIL;

    return S_OK;
}