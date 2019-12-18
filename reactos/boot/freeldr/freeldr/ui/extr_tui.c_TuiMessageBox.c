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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_TUI_SCREENBUFFER ; 
 int /*<<< orphan*/  TuiMessageBoxCritical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiRestoreScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiSaveScreen (int /*<<< orphan*/ ) ; 
 int UiScreenHeight ; 
 int UiScreenWidth ; 

VOID TuiMessageBox(PCSTR MessageText)
{
    PVOID    ScreenBuffer;

    // Save the screen contents
    ScreenBuffer = FrLdrTempAlloc(UiScreenWidth * UiScreenHeight * 2,
                                  TAG_TUI_SCREENBUFFER);
    TuiSaveScreen(ScreenBuffer);

    // Display the message box
    TuiMessageBoxCritical(MessageText);

    // Restore the screen contents
    TuiRestoreScreen(ScreenBuffer);
    FrLdrTempFree(ScreenBuffer, TAG_TUI_SCREENBUFFER);
}