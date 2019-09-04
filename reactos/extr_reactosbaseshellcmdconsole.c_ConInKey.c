#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ bKeyDown; } ;
struct TYPE_7__ {TYPE_1__ KeyEvent; } ;
struct TYPE_8__ {scalar_t__ EventType; TYPE_2__ Event; } ;
typedef  TYPE_3__* PINPUT_RECORD ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  ReadConsoleInput (scalar_t__,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 

VOID ConInKey(PINPUT_RECORD lpBuffer)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  dwRead;

    if (hInput == INVALID_HANDLE_VALUE)
        WARN ("Invalid input handle!!!\n");

    do
    {
        ReadConsoleInput(hInput, lpBuffer, 1, &dwRead);
        if (lpBuffer->EventType == KEY_EVENT &&
            lpBuffer->Event.KeyEvent.bKeyDown)
        {
            break;
        }
    }
    while (TRUE);
}