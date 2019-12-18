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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FileOpenDlgInfos ;

/* Variables and functions */
 int /*<<< orphan*/ * GetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filedlg_info_propnameW ; 

FileOpenDlgInfos *get_filedlg_infoptr(HWND hwnd)
{
    return GetPropW(hwnd, filedlg_info_propnameW);
}