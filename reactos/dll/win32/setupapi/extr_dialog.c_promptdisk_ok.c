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
struct promptdisk_params {int* PathRequiredSize; int PathBufferSize; int /*<<< orphan*/  PathBuffer; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DPROMPT_BUFFERTOOSMALL ; 
 int /*<<< orphan*/  DPROMPT_SUCCESS ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IDC_PATH ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void promptdisk_ok(HWND hwnd, struct promptdisk_params *params)
{
    int requiredSize;
    WCHAR aux[MAX_PATH];
    GetWindowTextW(GetDlgItem(hwnd, IDC_PATH), aux, MAX_PATH);
    requiredSize = strlenW(aux)+1;

    if(params->PathRequiredSize)
    {
        *params->PathRequiredSize = requiredSize;
        TRACE("returning PathRequiredSize=%d\n",*params->PathRequiredSize);
    }
    if(!params->PathBuffer)
    {
        EndDialog(hwnd, NO_ERROR);
        return;
    }
    if(requiredSize > params->PathBufferSize)
    {
        EndDialog(hwnd, DPROMPT_BUFFERTOOSMALL);
        return;
    }
    strcpyW(params->PathBuffer, aux);
    TRACE("returning PathBuffer=%s\n", debugstr_w(params->PathBuffer));
    EndDialog(hwnd, DPROMPT_SUCCESS);
}