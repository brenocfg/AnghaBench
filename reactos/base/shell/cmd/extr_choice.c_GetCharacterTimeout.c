#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  AsciiChar; int /*<<< orphan*/  UnicodeChar; } ;
struct TYPE_7__ {scalar_t__ bKeyDown; TYPE_1__ uChar; } ;
struct TYPE_8__ {TYPE_2__ KeyEvent; } ;
struct TYPE_9__ {scalar_t__ EventType; TYPE_3__ Event; } ;
typedef  int /*<<< orphan*/ * LPTCH ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_4__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GC_KEYREAD ; 
 int /*<<< orphan*/  GC_NOKEY ; 
 int /*<<< orphan*/  GC_TIMEOUT ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  ReadConsoleInput (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT
GetCharacterTimeout (LPTCH ch, DWORD dwMilliseconds)
{
//--------------------------------------------
//  Get a character from standard input but with a timeout.
//  The function will wait a limited amount
//  of time, then the function returns GC_TIMEOUT.
//
//  dwMilliseconds is the timeout value, that can
//  be set to INFINITE, so the function works like
//  stdio.h's getchar()

    HANDLE hInput;
    DWORD  dwRead;

    INPUT_RECORD lpBuffer;

    hInput = GetStdHandle (STD_INPUT_HANDLE);

    //if the timeout expired return GC_TIMEOUT
    if (WaitForSingleObject (hInput, dwMilliseconds) == WAIT_TIMEOUT)
        return GC_TIMEOUT;

    //otherwise get the event
    ReadConsoleInput (hInput, &lpBuffer, 1, &dwRead);

    //if the event is a key pressed
    if ((lpBuffer.EventType == KEY_EVENT) &&
        (lpBuffer.Event.KeyEvent.bKeyDown != FALSE))
    {
        //read the key
#ifdef _UNICODE
        *ch = lpBuffer.Event.KeyEvent.uChar.UnicodeChar;
#else
        *ch = lpBuffer.Event.KeyEvent.uChar.AsciiChar;
#endif
        return GC_KEYREAD;
    }

    //else return no key
    return GC_NOKEY;
}