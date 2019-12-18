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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MSG_SYNTAX_HELP ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdOut ; 

INT
cmdSyntax(INT argc, WCHAR **argv)
{
    PrintMessageString(4381);
    ConPuts(StdOut, L"\n");
    PrintNetMessage(MSG_SYNTAX_HELP);
    return 0;
}