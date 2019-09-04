#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t Operator; void* RightArg; void* LeftArg; int /*<<< orphan*/  Flags; } ;
struct TYPE_10__ {TYPE_2__* Subcommands; TYPE_1__ If; int /*<<< orphan*/  Type; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Next; } ;
typedef  TYPE_3__ PARSED_COMMAND ;

/* Variables and functions */
 int /*<<< orphan*/  C_IF ; 
 int /*<<< orphan*/  C_OP_LOWEST ; 
 scalar_t__* CurrentToken ; 
 int CurrentTokenType ; 
 int /*<<< orphan*/  FreeCommand (TYPE_3__*) ; 
 int /*<<< orphan*/  IFFLAG_IGNORECASE ; 
 int /*<<< orphan*/  IFFLAG_NEGATE ; 
 size_t IF_MAX_COMPARISON ; 
 size_t IF_MAX_UNARY ; 
 int /*<<< orphan*/ * IfOperatorString ; 
 void* ParseCommandOp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParseError () ; 
 int ParseToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STANDARD_SEPS ; 
 int TOK_NORMAL ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsicmp (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _tcsnicmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* cmd_alloc (int) ; 
 void* cmd_dup (scalar_t__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PARSED_COMMAND *ParseIf(void)
{
    int Type;
    PARSED_COMMAND *Cmd;

    Cmd = cmd_alloc(sizeof(PARSED_COMMAND));
    if (!Cmd)
    {
        WARN("Cannot allocate memory for Cmd!\n");
        ParseError();
        return NULL;
    }
    memset(Cmd, 0, sizeof(PARSED_COMMAND));
    Cmd->Type = C_IF;

    Type = CurrentTokenType;
    if (_tcsicmp(CurrentToken, _T("/I")) == 0)
    {
        Cmd->If.Flags |= IFFLAG_IGNORECASE;
        Type = ParseToken(0, STANDARD_SEPS);
    }
    if (_tcsicmp(CurrentToken, _T("not")) == 0)
    {
        Cmd->If.Flags |= IFFLAG_NEGATE;
        Type = ParseToken(0, STANDARD_SEPS);
    }

    if (Type != TOK_NORMAL)
    {
        FreeCommand(Cmd);
        ParseError();
        return NULL;
    }

    /* Check for unary operators */
    for (; Cmd->If.Operator <= IF_MAX_UNARY; Cmd->If.Operator++)
    {
        if (_tcsicmp(CurrentToken, IfOperatorString[Cmd->If.Operator]) == 0)
        {
            if (ParseToken(0, STANDARD_SEPS) != TOK_NORMAL)
            {
                FreeCommand(Cmd);
                ParseError();
                return NULL;
            }
            Cmd->If.RightArg = cmd_dup(CurrentToken);
            goto condition_done;
        }
    }

    /* It must be a two-argument (comparison) operator. It could be ==, so
     * the equals sign can't be treated as whitespace here. */
    Cmd->If.LeftArg = cmd_dup(CurrentToken);
    ParseToken(0, _T(",;"));

    /* The right argument can come immediately after == */
    if (_tcsnicmp(CurrentToken, _T("=="), 2) == 0 && CurrentToken[2])
    {
        Cmd->If.RightArg = cmd_dup(&CurrentToken[2]);
        goto condition_done;
    }

    for (; Cmd->If.Operator <= IF_MAX_COMPARISON; Cmd->If.Operator++)
    {
        if (_tcsicmp(CurrentToken, IfOperatorString[Cmd->If.Operator]) == 0)
        {
            if (ParseToken(0, STANDARD_SEPS) != TOK_NORMAL)
                break;
            Cmd->If.RightArg = cmd_dup(CurrentToken);
            goto condition_done;
        }
    }
    FreeCommand(Cmd);
    ParseError();
    return NULL;

condition_done:
    Cmd->Subcommands = ParseCommandOp(C_OP_LOWEST);
    if (Cmd->Subcommands == NULL)
    {
        FreeCommand(Cmd);
        return NULL;
    }
    if (_tcsicmp(CurrentToken, _T("else")) == 0)
    {
        Cmd->Subcommands->Next = ParseCommandOp(C_OP_LOWEST);
        if (Cmd->Subcommands->Next == NULL)
        {
            FreeCommand(Cmd);
            return NULL;
        }
    }

    return Cmd;
}