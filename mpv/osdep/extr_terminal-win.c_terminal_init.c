#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wAttributes; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int ENABLE_PROCESSED_OUTPUT ; 
 int ENABLE_WRAP_AT_EOL_OUTPUT ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hSTDERR ; 
 int /*<<< orphan*/  hSTDOUT ; 
 int /*<<< orphan*/  stdoutAttrs ; 

void terminal_init(void)
{
    CONSOLE_SCREEN_BUFFER_INFO cinfo;
    DWORD cmode = 0;
    GetConsoleMode(hSTDOUT, &cmode);
    cmode |= (ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
    SetConsoleMode(hSTDOUT, cmode);
    SetConsoleMode(hSTDERR, cmode);
    GetConsoleScreenBufferInfo(hSTDOUT, &cinfo);
    stdoutAttrs = cinfo.wAttributes;
}