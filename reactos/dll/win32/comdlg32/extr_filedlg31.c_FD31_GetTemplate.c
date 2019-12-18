#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* lpTemplateName; int /*<<< orphan*/  hInstance; } ;
struct TYPE_6__ {int Flags; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lpTemplateName; } ;
struct TYPE_5__ {void* template; scalar_t__ open; TYPE_3__* ofnA; TYPE_2__* ofnW; } ;
typedef  TYPE_1__* PFD31_DATA ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_2__* LPOPENFILENAMEW ;
typedef  TYPE_3__* LPOPENFILENAMEA ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDERR_FINDRESFAILURE ; 
 int /*<<< orphan*/  CDERR_LOADRESFAILURE ; 
 int /*<<< orphan*/  COMDLG32_SetCommDlgExtendedError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMDLG32_hInstance ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindResourceA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LockResource (int /*<<< orphan*/ ) ; 
 int OFN_ENABLETEMPLATE ; 
 int OFN_ENABLETEMPLATEHANDLE ; 
 scalar_t__ RT_DIALOG ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL FD31_GetTemplate(PFD31_DATA lfs)
{
    LPOPENFILENAMEW ofnW = lfs->ofnW;
    LPOPENFILENAMEA ofnA = lfs->ofnA;
    HANDLE hDlgTmpl;

    if (ofnW->Flags & OFN_ENABLETEMPLATEHANDLE)
    {
        if (!(lfs->template = LockResource( ofnW->hInstance )))
        {
            COMDLG32_SetCommDlgExtendedError( CDERR_LOADRESFAILURE );
            return FALSE;
        }
    }
    else if (ofnW->Flags & OFN_ENABLETEMPLATE)
    {
        HRSRC hResInfo;
        if (ofnA)
            hResInfo = FindResourceA( ofnA->hInstance, ofnA->lpTemplateName, (LPSTR)RT_DIALOG );
        else
            hResInfo = FindResourceW( ofnW->hInstance, ofnW->lpTemplateName, (LPWSTR)RT_DIALOG );
        if (!hResInfo)
        {
            COMDLG32_SetCommDlgExtendedError( CDERR_FINDRESFAILURE );
            return FALSE;
        }
        if (!(hDlgTmpl = LoadResource( ofnW->hInstance, hResInfo )) ||
            !(lfs->template = LockResource( hDlgTmpl )))
        {
            COMDLG32_SetCommDlgExtendedError( CDERR_LOADRESFAILURE );
            return FALSE;
        }
    }
    else /* get it from internal Wine resource */
    {
        HRSRC hResInfo;
        if (!(hResInfo = FindResourceA( COMDLG32_hInstance, lfs->open ? "OPEN_FILE" : "SAVE_FILE", (LPSTR)RT_DIALOG )))
        {
            COMDLG32_SetCommDlgExtendedError( CDERR_FINDRESFAILURE );
            return FALSE;
        }
        if (!(hDlgTmpl = LoadResource( COMDLG32_hInstance, hResInfo )) ||
            !(lfs->template = LockResource( hDlgTmpl )))
        {
            COMDLG32_SetCommDlgExtendedError( CDERR_LOADRESFAILURE );
            return FALSE;
        }
    }
    return TRUE;
}