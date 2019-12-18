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
typedef  int DWORD ;

/* Variables and functions */
 int ENABLE_EXTENDED_FLAGS ; 
 int ENABLE_INSERT_MODE ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID SetInsert(DWORD dwFlag)
{
    /*
     * NOTE: Enabling the ENABLE_INSERT_MODE mode can also be done by calling
     * kernel32:SetConsoleCommandHistoryMode(CONSOLE_OVERSTRIKE) (deprecated).
     */
    DWORD dwMode;
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hConsole, (dwMode & ~ENABLE_INSERT_MODE) | dwFlag);
}