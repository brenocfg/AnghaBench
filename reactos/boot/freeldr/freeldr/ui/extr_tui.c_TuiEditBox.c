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
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  char* PCSTR ;
typedef  char* PCHAR ;
typedef  int INT ;
typedef  scalar_t__ CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_HORZ ; 
 int /*<<< orphan*/  D_VERT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_BACKSPACE ; 
 scalar_t__ KEY_DELETE ; 
 scalar_t__ KEY_END ; 
 scalar_t__ KEY_ENTER ; 
 scalar_t__ KEY_ESC ; 
 scalar_t__ KEY_EXTENDED ; 
 scalar_t__ KEY_HOME ; 
 scalar_t__ KEY_LEFT ; 
 scalar_t__ KEY_RIGHT ; 
 int /*<<< orphan*/  MachBeep () ; 
 scalar_t__ MachConsGetCh () ; 
 scalar_t__ MachConsKbHit () ; 
 int /*<<< orphan*/  MachHwIdle () ; 
 int /*<<< orphan*/  MachVideoHideShowTextCursor (scalar_t__) ; 
 int /*<<< orphan*/  MachVideoSetTextCursorPosition (int,int) ; 
 int /*<<< orphan*/  TAG_TUI_SCREENBUFFER ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TuiDrawBox (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiRestoreScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiSaveScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiUpdateDateTime () ; 
 int /*<<< orphan*/  UiDrawStatusText (char*) ; 
 int /*<<< orphan*/  UiDrawText (int,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiDrawText2 (size_t,int,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiEditBoxBgColor ; 
 int /*<<< orphan*/  UiEditBoxTextColor ; 
 int /*<<< orphan*/  UiFillArea (size_t,int,size_t,int,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiMessageBoxBgColor ; 
 int /*<<< orphan*/  UiMessageBoxFgColor ; 
 int UiScreenHeight ; 
 int UiScreenWidth ; 
 int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM () ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int strlen (char*) ; 

BOOLEAN TuiEditBox(PCSTR MessageText, PCHAR EditTextBuffer, ULONG Length)
{
    INT        width = 8;
    ULONG    height = 1;
    INT        curline = 0;
    INT        k;
    size_t    i , j;
    INT        x1, x2, y1, y2;
    CHAR    temp[260];
    CHAR    key;
    BOOLEAN    Extended;
    INT        EditBoxLine;
    ULONG    EditBoxStartX, EditBoxEndX;
    INT        EditBoxCursorX;
    ULONG    EditBoxTextLength, EditBoxTextPosition;
    INT        EditBoxTextDisplayIndex;
    BOOLEAN    ReturnCode;
    PVOID    ScreenBuffer;

    // Save the screen contents
    ScreenBuffer = FrLdrTempAlloc(UiScreenWidth * UiScreenHeight * 2,
                                  TAG_TUI_SCREENBUFFER);
    TuiSaveScreen(ScreenBuffer);

    // Find the height
    for (i=0; i<strlen(MessageText); i++)
    {
        if (MessageText[i] == '\n')
            height++;
    }

    // Find the width
    for (i=0,j=0,k=0; i<height; i++)
    {
        while ((MessageText[j] != '\n') && (MessageText[j] != 0))
        {
            j++;
            k++;
        }

        if (k > width)
            width = k;

        k = 0;
        j++;
    }

    // Calculate box area
    x1 = (UiScreenWidth - (width+2))/2;
    x2 = x1 + width + 3;
    y1 = ((UiScreenHeight - height - 2)/2) + 1;
    y2 = y1 + height + 4;

    // Draw the box
    TuiDrawBox(x1, y1, x2, y2, D_VERT, D_HORZ, TRUE, TRUE, ATTR(UiMessageBoxFgColor, UiMessageBoxBgColor));

    // Draw the text
    for (i=0,j=0; i<strlen(MessageText)+1; i++)
    {
        if ((MessageText[i] == '\n') || (MessageText[i] == 0))
        {
            temp[j] = 0;
            j = 0;
            UiDrawText(x1+2, y1+1+curline, temp, ATTR(UiMessageBoxFgColor, UiMessageBoxBgColor));
            curline++;
        }
        else
            temp[j++] = MessageText[i];
    }

    EditBoxTextLength = (ULONG)strlen(EditTextBuffer);
    EditBoxTextLength = min(EditBoxTextLength, Length - 1);
    EditBoxTextPosition = 0;
    EditBoxLine = y2 - 2;
    EditBoxStartX = x1 + 3;
    EditBoxEndX = x2 - 3;

    // Draw the edit box background and the text
    UiFillArea(EditBoxStartX, EditBoxLine, EditBoxEndX, EditBoxLine, ' ', ATTR(UiEditBoxTextColor, UiEditBoxBgColor));
    UiDrawText2(EditBoxStartX, EditBoxLine, EditBoxEndX - EditBoxStartX + 1, EditTextBuffer, ATTR(UiEditBoxTextColor, UiEditBoxBgColor));

    // Show the cursor
    EditBoxCursorX = EditBoxStartX;
    MachVideoSetTextCursorPosition(EditBoxCursorX, EditBoxLine);
    MachVideoHideShowTextCursor(TRUE);

    // Draw status text
    UiDrawStatusText("Press ENTER to continue, or ESC to cancel");

    VideoCopyOffScreenBufferToVRAM();

    //
    // Enter the text. Please keep in mind that the default input mode
    // of the edit boxes is in insertion mode, that is, you can insert
    // text without erasing the existing one.
    //
    for (;;)
    {
        if (MachConsKbHit())
        {
            Extended = FALSE;
            key = MachConsGetCh();
            if (key == KEY_EXTENDED)
            {
                Extended = TRUE;
                key = MachConsGetCh();
            }

            if (key == KEY_ENTER)
            {
                ReturnCode = TRUE;
                break;
            }
            else if (key == KEY_ESC)
            {
                ReturnCode = FALSE;
                break;
            }
            else if (key == KEY_BACKSPACE) // Remove a character
            {
                if ( (EditBoxTextLength > 0) && (EditBoxTextPosition > 0) &&
                     (EditBoxTextPosition <= EditBoxTextLength) )
                {
                    EditBoxTextPosition--;
                    memmove(EditTextBuffer + EditBoxTextPosition,
                            EditTextBuffer + EditBoxTextPosition + 1,
                            EditBoxTextLength - EditBoxTextPosition);
                    EditBoxTextLength--;
                    EditTextBuffer[EditBoxTextLength] = 0;
                }
                else
                {
                    MachBeep();
                }
            }
            else if (Extended && key == KEY_DELETE) // Remove a character
            {
                if ( (EditBoxTextLength > 0) &&
                     (EditBoxTextPosition < EditBoxTextLength) )
                {
                    memmove(EditTextBuffer + EditBoxTextPosition,
                            EditTextBuffer + EditBoxTextPosition + 1,
                            EditBoxTextLength - EditBoxTextPosition);
                    EditBoxTextLength--;
                    EditTextBuffer[EditBoxTextLength] = 0;
                }
                else
                {
                    MachBeep();
                }
            }
            else if (Extended && key == KEY_HOME) // Go to the start of the buffer
            {
                EditBoxTextPosition = 0;
            }
            else if (Extended && key == KEY_END) // Go to the end of the buffer
            {
                EditBoxTextPosition = EditBoxTextLength;
            }
            else if (Extended && key == KEY_RIGHT) // Go right
            {
                if (EditBoxTextPosition < EditBoxTextLength)
                    EditBoxTextPosition++;
                else
                    MachBeep();
            }
            else if (Extended && key == KEY_LEFT) // Go left
            {
                if (EditBoxTextPosition > 0)
                    EditBoxTextPosition--;
                else
                    MachBeep();
            }
            else if (!Extended) // Add this key to the buffer
            {
                if ( (EditBoxTextLength   < Length - 1) &&
                     (EditBoxTextPosition < Length - 1) )
                {
                    memmove(EditTextBuffer + EditBoxTextPosition + 1,
                            EditTextBuffer + EditBoxTextPosition,
                            EditBoxTextLength - EditBoxTextPosition);
                    EditTextBuffer[EditBoxTextPosition] = key;
                    EditBoxTextPosition++;
                    EditBoxTextLength++;
                    EditTextBuffer[EditBoxTextLength] = 0;
                }
                else
                {
                    MachBeep();
                }
            }
            else
            {
                MachBeep();
            }
        }

        // Draw the edit box background
        UiFillArea(EditBoxStartX, EditBoxLine, EditBoxEndX, EditBoxLine, ' ', ATTR(UiEditBoxTextColor, UiEditBoxBgColor));

        // Fill the text in
        if (EditBoxTextPosition > (EditBoxEndX - EditBoxStartX))
        {
            EditBoxTextDisplayIndex = EditBoxTextPosition - (EditBoxEndX - EditBoxStartX);
            EditBoxCursorX = EditBoxEndX;
        }
        else
        {
            EditBoxTextDisplayIndex = 0;
            EditBoxCursorX = EditBoxStartX + EditBoxTextPosition;
        }
        UiDrawText2(EditBoxStartX, EditBoxLine, EditBoxEndX - EditBoxStartX + 1, &EditTextBuffer[EditBoxTextDisplayIndex], ATTR(UiEditBoxTextColor, UiEditBoxBgColor));

        // Move the cursor
        MachVideoSetTextCursorPosition(EditBoxCursorX, EditBoxLine);

        TuiUpdateDateTime();

        VideoCopyOffScreenBufferToVRAM();

        MachHwIdle();
    }

    // Hide the cursor again
    MachVideoHideShowTextCursor(FALSE);

    // Restore the screen contents
    TuiRestoreScreen(ScreenBuffer);
    FrLdrTempFree(ScreenBuffer, TAG_TUI_SCREENBUFFER);

    return ReturnCode;
}