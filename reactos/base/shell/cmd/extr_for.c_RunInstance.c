#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Type; } ;
struct TYPE_5__ {TYPE_3__* Subcommands; } ;
typedef  TYPE_1__ PARSED_COMMAND ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 scalar_t__ C_QUIET ; 
 int /*<<< orphan*/  ConOutChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EchoCommand (TYPE_3__*) ; 
 int /*<<< orphan*/  ExecuteCommand (TYPE_3__*) ; 
 int /*<<< orphan*/  PrintPrompt () ; 
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/  bDisableBatchEcho ; 
 scalar_t__ bEcho ; 
 int /*<<< orphan*/  bIgnoreEcho ; 

__attribute__((used)) static INT RunInstance(PARSED_COMMAND *Cmd)
{
    if (bEcho && !bDisableBatchEcho && Cmd->Subcommands->Type != C_QUIET)
    {
        if (!bIgnoreEcho)
            ConOutChar(_T('\n'));
        PrintPrompt();
        EchoCommand(Cmd->Subcommands);
        ConOutChar(_T('\n'));
    }
    /* Just run the command (variable expansion is done in DoDelayedExpansion) */
    return ExecuteCommand(Cmd->Subcommands);
}