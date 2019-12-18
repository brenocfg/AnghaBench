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
struct TYPE_2__ {scalar_t__* szFileTitle; int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  hEdit; int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EM_GETMODIFY ; 
 scalar_t__ FALSE ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 int /*<<< orphan*/  STRING_NOTEPAD ; 
 int /*<<< orphan*/  STRING_UNTITLED ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbPrintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  StringCchCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 

void UpdateWindowCaption(BOOL clearModifyAlert)
{
    TCHAR szCaption[MAX_STRING_LEN];
    TCHAR szNotepad[MAX_STRING_LEN];
    TCHAR szFilename[MAX_STRING_LEN];

    /* Load the name of the application */
    LoadString(Globals.hInstance, STRING_NOTEPAD, szNotepad, ARRAY_SIZE(szNotepad));

    /* Determine if the file has been saved or if this is a new file */
    if (Globals.szFileTitle[0] != 0)
        StringCchCopy(szFilename, ARRAY_SIZE(szFilename), Globals.szFileTitle);
    else
        LoadString(Globals.hInstance, STRING_UNTITLED, szFilename, ARRAY_SIZE(szFilename));

    /* When a file is being opened or created, there is no need to have the edited flag shown
       when the new or opened file has not been edited yet */
    if (clearModifyAlert)
        StringCbPrintf(szCaption, ARRAY_SIZE(szCaption), _T("%s - %s"), szFilename, szNotepad);
    else
    {
        BOOL isModified = (SendMessage(Globals.hEdit, EM_GETMODIFY, 0, 0) ? TRUE : FALSE);

        /* Update the caption based upon if the user has modified the contents of the file or not */
        StringCbPrintf(szCaption, ARRAY_SIZE(szCaption), _T("%s%s - %s"),
            (isModified ? _T("*") : _T("")), szFilename, szNotepad);
    }

    /* Update the window caption */
    SetWindowText(Globals.hMainWnd, szCaption);
}