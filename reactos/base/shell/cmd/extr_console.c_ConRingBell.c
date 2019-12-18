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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  Beep (int,int) ; 
 int /*<<< orphan*/  ConOutPuts (int /*<<< orphan*/ ) ; 
 scalar_t__ IsConsoleHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ IsTTYHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageBeep (int) ; 
 int /*<<< orphan*/  _T (char*) ; 

VOID ConRingBell(HANDLE hOutput)
{
#if 0
    /* Emit an error beep sound */
    if (IsConsoleHandle(hOutput))
        Beep(800, 200);
    else if (IsTTYHandle(hOutput))
        ConOutPuts(_T("\a")); // BEL character 0x07
    else
#endif
        MessageBeep(-1);
}