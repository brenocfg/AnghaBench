#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int UnicodeChar; } ;
struct TYPE_9__ {int dwControlKeyState; int wVirtualKeyCode; TYPE_1__ uChar; } ;
struct TYPE_10__ {TYPE_2__ KeyEvent; } ;
struct TYPE_12__ {TYPE_3__ Event; } ;
struct TYPE_11__ {int maxx; int maxy; scalar_t__ bInsert; } ;
typedef  int SHORT ;
typedef  TYPE_4__* PCONSOLE_STATE ;
typedef  int* LPSTR ;
typedef  int* LPCSTR ;
typedef  int INT ;
typedef  TYPE_5__ INPUT_RECORD ;
typedef  int CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_ConInKey (TYPE_5__*) ; 
 int /*<<< orphan*/  CONSOLE_ConOutChar (int) ; 
 int /*<<< orphan*/  CONSOLE_ConOutPrintf (char*,...) ; 
 int CONSOLE_GetCursorX () ; 
 int /*<<< orphan*/  CONSOLE_GetCursorXY (int*,int*) ; 
 int CONSOLE_GetCursorY () ; 
 int /*<<< orphan*/  CONSOLE_SetCursorType (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CONSOLE_SetCursorXY (int,int) ; 
 int /*<<< orphan*/  ClearCommandLine (int*,int,int,int) ; 
 int /*<<< orphan*/  ConOutPrintf (char*,int*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCursorXY (int*,int*) ; 
 int /*<<< orphan*/  History (int,int*) ; 
 int /*<<< orphan*/  History_del_current_entry (int*) ; 
 int /*<<< orphan*/  History_move_to_bottom () ; 
 int LEFT_ALT_PRESSED ; 
 int LEFT_CTRL_PRESSED ; 
 int* PeekHistory (int) ; 
 int RIGHT_ALT_PRESSED ; 
 int RIGHT_CTRL_PRESSED ; 
 scalar_t__ TRUE ; 
#define  VK_BACK 139 
#define  VK_DELETE 138 
#define  VK_DOWN 137 
#define  VK_END 136 
#define  VK_ESCAPE 135 
#define  VK_F3 134 
#define  VK_HOME 133 
#define  VK_INSERT 132 
#define  VK_LEFT 131 
#define  VK_RETURN 130 
#define  VK_RIGHT 129 
#define  VK_UP 128 
 int maxx ; 
 scalar_t__ maxy ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int strlen (int*) ; 

__attribute__((used)) static
BOOL
ReadCommand(
    PCONSOLE_STATE State,
    LPSTR str,
    INT maxlen)
{
    SHORT orgx;     /* origin x/y */
    SHORT orgy;
    SHORT curx;     /*current x/y cursor position*/
    SHORT cury;
    SHORT tempscreen;
    INT   count;    /*used in some for loops*/
    INT   current = 0;  /*the position of the cursor in the string (str)*/
    INT   charcount = 0;/*chars in the string (str)*/
    INPUT_RECORD ir;
    CHAR  ch;
    BOOL bReturn = FALSE;
    BOOL bCharInput;
#ifdef FEATURE_HISTORY
    //BOOL bContinue=FALSE;/*is TRUE the second case will not be executed*/
    CHAR PreviousChar;
#endif


    CONSOLE_GetCursorXY(&orgx, &orgy);
    curx = orgx;
    cury = orgy;

    memset(str, 0, maxlen * sizeof(CHAR));

    CONSOLE_SetCursorType(State->bInsert, TRUE);

    do
    {
        bReturn = FALSE;
        CONSOLE_ConInKey(&ir);

        if (ir.Event.KeyEvent.dwControlKeyState &
            (RIGHT_ALT_PRESSED |LEFT_ALT_PRESSED|
             RIGHT_CTRL_PRESSED|LEFT_CTRL_PRESSED) )
        {
            switch (ir.Event.KeyEvent.wVirtualKeyCode)
            {
#ifdef FEATURE_HISTORY
                case 'K':
                    /*add the current command line to the history*/
                    if (ir.Event.KeyEvent.dwControlKeyState &
                        (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED))
                    {
                        if (str[0])
                            History(0,str);

                        ClearCommandLine (str, maxlen, orgx, orgy);
                        current = charcount = 0;
                        curx = orgx;
                        cury = orgy;
                        //bContinue=TRUE;
                        break;
                    }

                case 'D':
                    /*delete current history entry*/
                    if (ir.Event.KeyEvent.dwControlKeyState &
                        (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED))
                    {
                        ClearCommandLine (str, maxlen, orgx, orgy);
                        History_del_current_entry(str);
                        current = charcount = strlen (str);
                        ConOutPrintf("%s", str);
                        GetCursorXY(&curx, &cury);
                        //bContinue=TRUE;
                        break;
                    }

#endif /*FEATURE_HISTORY*/
            }
        }

        bCharInput = FALSE;

        switch (ir.Event.KeyEvent.wVirtualKeyCode)
        {
            case VK_BACK:
                /* <BACKSPACE> - delete character to left of cursor */
                if (current > 0 && charcount > 0)
                {
                    if (current == charcount)
                    {
                        /* if at end of line */
                        str[current - 1] = L'\0';
                        if (CONSOLE_GetCursorX () != 0)
                        {
                            CONSOLE_ConOutPrintf("\b \b");
                            curx--;
                        }
                        else
                        {
                            CONSOLE_SetCursorXY((SHORT)(State->maxx - 1), (SHORT)(CONSOLE_GetCursorY () - 1));
                            CONSOLE_ConOutChar(' ');
                            CONSOLE_SetCursorXY((SHORT)(State->maxx - 1), (SHORT)(CONSOLE_GetCursorY () - 1));
                            cury--;
                            curx = State->maxx - 1;
                        }
                    }
                    else
                    {
                        for (count = current - 1; count < charcount; count++)
                            str[count] = str[count + 1];
                        if (CONSOLE_GetCursorX () != 0)
                        {
                            CONSOLE_SetCursorXY ((SHORT)(CONSOLE_GetCursorX () - 1), CONSOLE_GetCursorY ());
                            curx--;
                        }
                        else
                        {
                            CONSOLE_SetCursorXY ((SHORT)(State->maxx - 1), (SHORT)(CONSOLE_GetCursorY () - 1));
                            cury--;
                            curx = State->maxx - 1;
                        }
                        CONSOLE_GetCursorXY(&curx, &cury);
                        CONSOLE_ConOutPrintf("%s ", &str[current - 1]);
                        CONSOLE_SetCursorXY(curx, cury);
                    }
                    charcount--;
                    current--;
                }
                break;

            case VK_INSERT:
                /* toggle insert/overstrike mode */
                State->bInsert ^= TRUE;
                CONSOLE_SetCursorType(State->bInsert, TRUE);
                break;

            case VK_DELETE:
                /* delete character under cursor */
                if (current != charcount && charcount > 0)
                {
                    for (count = current; count < charcount; count++)
                        str[count] = str[count + 1];
                    charcount--;
                    CONSOLE_GetCursorXY(&curx, &cury);
                    CONSOLE_ConOutPrintf("%s ", &str[current]);
                    CONSOLE_SetCursorXY(curx, cury);
                }
                break;

            case VK_HOME:
                /* goto beginning of string */
                if (current != 0)
                {
                    CONSOLE_SetCursorXY(orgx, orgy);
                    curx = orgx;
                    cury = orgy;
                    current = 0;
                }
                break;

            case VK_END:
                /* goto end of string */
                if (current != charcount)
                {
                    CONSOLE_SetCursorXY(orgx, orgy);
                    CONSOLE_ConOutPrintf("%s", str);
                    CONSOLE_GetCursorXY(&curx, &cury);
                    current = charcount;
                }
                break;

            case 'M':
            case 'C':
                /* ^M does the same as return */
                bCharInput = TRUE;
                if (!(ir.Event.KeyEvent.dwControlKeyState &
                    (RIGHT_CTRL_PRESSED|LEFT_CTRL_PRESSED)))
                {
                    break;
                }

            case VK_RETURN:
                /* end input, return to main */
#ifdef FEATURE_HISTORY
                /* add to the history */
                if (str[0])
                    History (0, str);
#endif
                str[charcount] = '\0';
                CONSOLE_ConOutChar('\n');
                bReturn = TRUE;
                break;

            case VK_ESCAPE:
                /* clear str  Make this callable! */
                ClearCommandLine (str, maxlen, orgx, orgy);
                curx = orgx;
                cury = orgy;
                current = charcount = 0;
                break;

#ifdef FEATURE_HISTORY
            case VK_F3:
                History_move_to_bottom();
#endif
            case VK_UP:
#ifdef FEATURE_HISTORY
                /* get previous command from buffer */
                ClearCommandLine (str, maxlen, orgx, orgy);
                History (-1, str);
                current = charcount = strlen (str);
                if (((charcount + orgx) / maxx) + orgy > maxy - 1)
                    orgy += maxy - ((charcount + orgx) / maxx + orgy + 1);
                CONSOLE_ConOutPrintf("%s", str);
                CONSOLE_GetCursorXY(&curx, &cury);
#endif
                break;

            case VK_DOWN:
#ifdef FEATURE_HISTORY
                /* get next command from buffer */
                ClearCommandLine (str, maxlen, orgx, orgy);
                History (1, str);
                current = charcount = strlen (str);
                if (((charcount + orgx) / maxx) + orgy > maxy - 1)
                    orgy += maxy - ((charcount + orgx) / maxx + orgy + 1);
                CONSOLE_ConOutPrintf("%s", str);
                CONSOLE_GetCursorXY(&curx, &cury);
#endif
                break;

            case VK_LEFT:
                /* move cursor left */
                if (current > 0)
                {
                    current--;
                    if (CONSOLE_GetCursorX() == 0)
                    {
                        CONSOLE_SetCursorXY((SHORT)(State->maxx - 1), (SHORT)(CONSOLE_GetCursorY () - 1));
                        curx = State->maxx - 1;
                        cury--;
                    }
                    else
                    {
                        CONSOLE_SetCursorXY((SHORT)(CONSOLE_GetCursorX () - 1), CONSOLE_GetCursorY ());
                        curx--;
                    }
                }
                break;

            case VK_RIGHT:
                /* move cursor right */
                if (current != charcount)
                {
                    current++;
                    if (CONSOLE_GetCursorX() == State->maxx - 1)
                    {
                        CONSOLE_SetCursorXY(0, (SHORT)(CONSOLE_GetCursorY () + 1));
                        curx = 0;
                        cury++;
                    }
                    else
                    {
                        CONSOLE_SetCursorXY((SHORT)(CONSOLE_GetCursorX () + 1), CONSOLE_GetCursorY ());
                        curx++;
                    }
                }
#ifdef FEATURE_HISTORY
                else
                {
                    LPCSTR last = PeekHistory(-1);
                    if (last && charcount < (INT)strlen (last))
                    {
                        PreviousChar = last[current];
                        CONSOLE_ConOutChar(PreviousChar);
                        CONSOLE_GetCursorXY(&curx, &cury);
                        str[current++] = PreviousChar;
                        charcount++;
                    }
                }
#endif
                break;

            default:
                /* This input is just a normal char */
                bCharInput = TRUE;

        }

        ch = ir.Event.KeyEvent.uChar.UnicodeChar;
        if (ch >= 32 && (charcount != (maxlen - 2)) && bCharInput)
        {
            /* insert character into string... */
            if (State->bInsert && current != charcount)
            {
                /* If this character insertion will cause screen scrolling,
                 * adjust the saved origin of the command prompt. */
                tempscreen = strlen(str + current) + curx;
                if ((tempscreen % State->maxx) == (State->maxx - 1) &&
                    (tempscreen / State->maxx) + cury == (State->maxy - 1))
                {
                    orgy--;
                    cury--;
                }

                for (count = charcount; count > current; count--)
                    str[count] = str[count - 1];
                str[current++] = ch;
                if (curx == State->maxx - 1)
                    curx = 0, cury++;
                else
                    curx++;
                CONSOLE_ConOutPrintf("%s", &str[current - 1]);
                CONSOLE_SetCursorXY(curx, cury);
                charcount++;
            }
            else
            {
                if (current == charcount)
                    charcount++;
                str[current++] = ch;
                if (CONSOLE_GetCursorX () == State->maxx - 1 && CONSOLE_GetCursorY () == State->maxy - 1)
                    orgy--, cury--;
                if (CONSOLE_GetCursorX () == State->maxx - 1)
                    curx = 0, cury++;
                else
                    curx++;
                CONSOLE_ConOutChar(ch);
            }
        }
    }
    while (!bReturn);

    CONSOLE_SetCursorType(State->bInsert, TRUE);

    return TRUE;
}