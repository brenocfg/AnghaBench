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
struct TYPE_2__ {int /*<<< orphan*/  hMainWnd; } ;
typedef  int /*<<< orphan*/  LPCTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DIALOG_StringMsgBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ Globals ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  STRING_NOTFOUND ; 

__attribute__((used)) static void AlertFileNotFound(LPCTSTR szFileName)
{
    DIALOG_StringMsgBox(Globals.hMainWnd, STRING_NOTFOUND, szFileName, MB_ICONEXCLAMATION | MB_OK);
}