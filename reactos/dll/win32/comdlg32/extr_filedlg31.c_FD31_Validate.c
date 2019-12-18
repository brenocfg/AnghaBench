#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ofnsav ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  fileokstring; scalar_t__ hook; int /*<<< orphan*/  lbselchstring; TYPE_1__* ofnW; int /*<<< orphan*/  hwnd; } ;
struct TYPE_11__ {int Flags; char* lpstrFile; int /*<<< orphan*/  lStructSize; } ;
typedef  TYPE_1__ OPENFILENAMEW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  char* LPWSTR ;
typedef  TYPE_1__* LPOPENFILENAMEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ FD31_DATA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BUFFILE ; 
 int /*<<< orphan*/  CD_LBSELCHANGE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FD31_CallWindowProc (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD31_TestPath (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD31_UpdateFileTitle (TYPE_3__ const*) ; 
 int /*<<< orphan*/  FD31_UpdateResult (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OFN_ALLOWMULTISELECT ; 
 int OFN_EXPLORER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edt1 ; 
 int /*<<< orphan*/  lst1 ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 char* wcsrchr (char*,char) ; 

__attribute__((used)) static LRESULT FD31_Validate( const FD31_DATA *lfs, LPCWSTR path, UINT control, INT itemIndex,
                                 BOOL internalUse )
{
    LONG lRet;
    HWND hWnd = lfs->hwnd;
    OPENFILENAMEW ofnsav;
    LPOPENFILENAMEW ofnW = lfs->ofnW;
    WCHAR filename[BUFFILE];
    int copied_size = min( ofnW->lStructSize, sizeof(ofnsav) );

    memcpy( &ofnsav, ofnW, copied_size ); /* for later restoring */

    /* get current file name */
    if (path)
        lstrcpynW(filename, path, ARRAY_SIZE(filename));
    else
        GetDlgItemTextW( hWnd, edt1, filename, ARRAY_SIZE(filename));

    TRACE("got filename = %s\n", debugstr_w(filename));
    /* if we did not click in file list to get there */
    if (control != lst1)
    {
        if (!FD31_TestPath( lfs, filename) )
           return FALSE;
    }
    FD31_UpdateResult(lfs, filename);

    if (internalUse)
    { /* called internally after a change in a combo */
        if (lfs->hook)
        {
             FD31_CallWindowProc(lfs, lfs->lbselchstring, control,
                             MAKELONG(itemIndex,CD_LBSELCHANGE));
        }
        return TRUE;
    }

    FD31_UpdateFileTitle(lfs);
    if (lfs->hook)
    {
        lRet = FD31_CallWindowProc(lfs, lfs->fileokstring,
                  0, lfs->lParam );
        if (lRet)
        {
            memcpy( ofnW, &ofnsav, copied_size ); /* restore old state */
            return FALSE;
        }
    }
    if ((ofnW->Flags & OFN_ALLOWMULTISELECT) && (ofnW->Flags & OFN_EXPLORER))
    {
        if (ofnW->lpstrFile)
        {
            LPWSTR str = ofnW->lpstrFile;
            LPWSTR ptr = wcsrchr(str, '\\');
	    str[lstrlenW(str) + 1] = '\0';
	    *ptr = 0;
        }
    }
    return TRUE;
}