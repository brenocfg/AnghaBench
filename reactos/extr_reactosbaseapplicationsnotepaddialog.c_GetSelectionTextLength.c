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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EM_GETSEL ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int GetSelectionTextLength(HWND hWnd)
{
    DWORD dwStart = 0;
    DWORD dwEnd = 0;

    SendMessage(hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);

    return dwEnd - dwStart;
}