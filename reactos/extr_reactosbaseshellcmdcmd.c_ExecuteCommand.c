#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Rest; int /*<<< orphan*/  First; } ;
struct TYPE_9__ {int Type; int /*<<< orphan*/  Redirections; struct TYPE_9__* Next; struct TYPE_9__* Subcommands; TYPE_1__ Command; } ;
typedef  TYPE_2__ PARSED_COMMAND ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int INT ;

/* Variables and functions */
#define  C_BLOCK 136 
#define  C_COMMAND 135 
#define  C_FOR 134 
#define  C_IF 133 
#define  C_IFFAILURE 132 
#define  C_IFSUCCESS 131 
#define  C_MULTI 130 
#define  C_PIPE 129 
#define  C_QUIET 128 
 int DoCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DoDelayedExpansion (int /*<<< orphan*/ ) ; 
 int ExecuteFor (TYPE_2__*) ; 
 int ExecuteIf (TYPE_2__*) ; 
 int ExecutePipeline (TYPE_2__*) ; 
 int /*<<< orphan*/  PerformRedirection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UndoRedirection (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_free (int /*<<< orphan*/ ) ; 
 int nErrorLevel ; 

INT
ExecuteCommand(PARSED_COMMAND *Cmd)
{
    PARSED_COMMAND *Sub;
    LPTSTR First, Rest;
    INT Ret = 0;

    if (!PerformRedirection(Cmd->Redirections))
        return 1;

    switch (Cmd->Type)
    {
    case C_COMMAND:
        Ret = 1;
        First = DoDelayedExpansion(Cmd->Command.First);
        if (First)
        {
            Rest = DoDelayedExpansion(Cmd->Command.Rest);
            if (Rest)
            {
                Ret = DoCommand(First, Rest, Cmd);
                cmd_free(Rest);
            }
            cmd_free(First);
        }
        break;
    case C_QUIET:
    case C_BLOCK:
    case C_MULTI:
        for (Sub = Cmd->Subcommands; Sub; Sub = Sub->Next)
            Ret = ExecuteCommand(Sub);
        break;
    case C_IFFAILURE:
        Sub = Cmd->Subcommands;
        Ret = ExecuteCommand(Sub);
        if (Ret != 0)
        {
            nErrorLevel = Ret;
            Ret = ExecuteCommand(Sub->Next);
        }
        break;
    case C_IFSUCCESS:
        Sub = Cmd->Subcommands;
        Ret = ExecuteCommand(Sub);
        if (Ret == 0)
            Ret = ExecuteCommand(Sub->Next);
        break;
    case C_PIPE:
        Ret = ExecutePipeline(Cmd);
        break;
    case C_IF:
        Ret = ExecuteIf(Cmd);
        break;
    case C_FOR:
        Ret = ExecuteFor(Cmd);
        break;
    }

    UndoRedirection(Cmd->Redirections, NULL);
    return Ret;
}