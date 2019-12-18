#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * Redirections; struct TYPE_6__* Next; struct TYPE_6__* Subcommands; int /*<<< orphan*/  Type; } ;
typedef  int /*<<< orphan*/  REDIRECTION ;
typedef  TYPE_1__ PARSED_COMMAND ;

/* Variables and functions */
 int /*<<< orphan*/  C_BLOCK ; 
 int /*<<< orphan*/  C_OP_LOWEST ; 
 scalar_t__ CurrentTokenType ; 
 int /*<<< orphan*/  FreeCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeRedirection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsideBlock ; 
 int /*<<< orphan*/  ParseChar () ; 
 TYPE_1__* ParseCommandOp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParseError () ; 
 int /*<<< orphan*/  ParseRedirection (int /*<<< orphan*/ **) ; 
 scalar_t__ ParseToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STANDARD_SEPS ; 
 scalar_t__ TOK_END_BLOCK ; 
 scalar_t__ TOK_REDIRECTION ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ bParseError ; 
 TYPE_1__* cmd_alloc (int) ; 

__attribute__((used)) static PARSED_COMMAND *ParseBlock(REDIRECTION *RedirList)
{
    PARSED_COMMAND *Cmd, *Sub, **NextPtr;

    Cmd = cmd_alloc(sizeof(PARSED_COMMAND));
    if (!Cmd)
    {
        WARN("Cannot allocate memory for Cmd!\n");
        ParseError();
        FreeRedirection(RedirList);
        return NULL;
    }
    Cmd->Type = C_BLOCK;
    Cmd->Next = NULL;
    Cmd->Subcommands = NULL;
    Cmd->Redirections = RedirList;

    /* Read the block contents */
    NextPtr = &Cmd->Subcommands;
    InsideBlock++;
    while (1)
    {
        Sub = ParseCommandOp(C_OP_LOWEST);
        if (Sub)
        {
            *NextPtr = Sub;
            NextPtr = &Sub->Next;
        }
        else if (bParseError)
        {
            InsideBlock--;
            FreeCommand(Cmd);
            return NULL;
        }

        if (CurrentTokenType == TOK_END_BLOCK)
            break;

        /* Skip past the \n */
        ParseChar();
    }
    InsideBlock--;

    /* Process any trailing redirections */
    while (ParseToken(0, STANDARD_SEPS) == TOK_REDIRECTION)
    {
        if (!ParseRedirection(&Cmd->Redirections))
        {
            FreeCommand(Cmd);
            return NULL;
        }
    }
    return Cmd;
}