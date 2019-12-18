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
typedef  int WPARAM ;

/* Variables and functions */
#define  CMD_COPY 150 
#define  CMD_CUT 149 
#define  CMD_DELETE 148 
#define  CMD_EXIT 147 
#define  CMD_FONT 146 
#define  CMD_GOTO 145 
#define  CMD_HELP_ABOUT_NOTEPAD 144 
#define  CMD_HELP_CONTENTS 143 
#define  CMD_NEW 142 
#define  CMD_OPEN 141 
#define  CMD_PAGE_SETUP 140 
#define  CMD_PASTE 139 
#define  CMD_PRINT 138 
#define  CMD_REPLACE 137 
#define  CMD_SAVE 136 
#define  CMD_SAVE_AS 135 
#define  CMD_SEARCH 134 
#define  CMD_SEARCH_NEXT 133 
#define  CMD_SELECT_ALL 132 
#define  CMD_STATUSBAR 131 
#define  CMD_TIME_DATE 130 
#define  CMD_UNDO 129 
#define  CMD_WRAP 128 
 int /*<<< orphan*/  DIALOG_EditCopy () ; 
 int /*<<< orphan*/  DIALOG_EditCut () ; 
 int /*<<< orphan*/  DIALOG_EditDelete () ; 
 int /*<<< orphan*/  DIALOG_EditPaste () ; 
 int /*<<< orphan*/  DIALOG_EditSelectAll () ; 
 int /*<<< orphan*/  DIALOG_EditTimeDate () ; 
 int /*<<< orphan*/  DIALOG_EditUndo () ; 
 int /*<<< orphan*/  DIALOG_EditWrap () ; 
 int /*<<< orphan*/  DIALOG_FileExit () ; 
 int /*<<< orphan*/  DIALOG_FileNew () ; 
 int /*<<< orphan*/  DIALOG_FileOpen () ; 
 int /*<<< orphan*/  DIALOG_FilePageSetup () ; 
 int /*<<< orphan*/  DIALOG_FilePrint () ; 
 int /*<<< orphan*/  DIALOG_FileSave () ; 
 int /*<<< orphan*/  DIALOG_FileSaveAs () ; 
 int /*<<< orphan*/  DIALOG_GoTo () ; 
 int /*<<< orphan*/  DIALOG_HelpAboutNotepad () ; 
 int /*<<< orphan*/  DIALOG_HelpContents () ; 
 int /*<<< orphan*/  DIALOG_Replace () ; 
 int /*<<< orphan*/  DIALOG_Search () ; 
 int /*<<< orphan*/  DIALOG_SearchNext () ; 
 int /*<<< orphan*/  DIALOG_SelectFont () ; 
 int /*<<< orphan*/  DIALOG_ViewStatusBar () ; 

__attribute__((used)) static int NOTEPAD_MenuCommand(WPARAM wParam)
{
    switch (wParam)
    {
    case CMD_NEW:        DIALOG_FileNew(); break;
    case CMD_OPEN:       DIALOG_FileOpen(); break;
    case CMD_SAVE:       DIALOG_FileSave(); break;
    case CMD_SAVE_AS:    DIALOG_FileSaveAs(); break;
    case CMD_PRINT:      DIALOG_FilePrint(); break;
    case CMD_PAGE_SETUP: DIALOG_FilePageSetup(); break;
    case CMD_EXIT:       DIALOG_FileExit(); break;

    case CMD_UNDO:       DIALOG_EditUndo(); break;
    case CMD_CUT:        DIALOG_EditCut(); break;
    case CMD_COPY:       DIALOG_EditCopy(); break;
    case CMD_PASTE:      DIALOG_EditPaste(); break;
    case CMD_DELETE:     DIALOG_EditDelete(); break;
    case CMD_SELECT_ALL: DIALOG_EditSelectAll(); break;
    case CMD_TIME_DATE:  DIALOG_EditTimeDate(); break;

    case CMD_SEARCH:      DIALOG_Search(); break;
    case CMD_SEARCH_NEXT: DIALOG_SearchNext(); break;
    case CMD_REPLACE:     DIALOG_Replace(); break;
    case CMD_GOTO:        DIALOG_GoTo(); break;

    case CMD_WRAP: DIALOG_EditWrap(); break;
    case CMD_FONT: DIALOG_SelectFont(); break;

    case CMD_STATUSBAR: DIALOG_ViewStatusBar(); break;

    case CMD_HELP_CONTENTS: DIALOG_HelpContents(); break;
    case CMD_HELP_ABOUT_NOTEPAD: DIALOG_HelpAboutNotepad(); break;

    default:
        break;
    }
    return 0;
}