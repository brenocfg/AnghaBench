#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_23__ {int Size; TYPE_6__* Arg; } ;
struct TYPE_24__ {TYPE_2__ Value; int /*<<< orphan*/  AmlOpcode; TYPE_6__* Next; } ;
struct TYPE_22__ {int /*<<< orphan*/  Data; } ;
struct TYPE_27__ {TYPE_3__ Common; TYPE_1__ Named; } ;
struct TYPE_26__ {int /*<<< orphan*/  PkgEnd; int /*<<< orphan*/  Aml; } ;
struct TYPE_25__ {int ArgCount; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_STATE ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ACPI_IS_PARENT_PREFIX (int) ; 
 int /*<<< orphan*/  ACPI_IS_ROOT_PREFIX (int) ; 
 int /*<<< orphan*/  ACPI_NOT_METHOD_CALL ; 
 int /*<<< orphan*/  ACPI_POSSIBLE_METHOD_CALL ; 
 int /*<<< orphan*/  ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ACPI_VAR_ARGS ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AML_BYTE_OP ; 
 int /*<<< orphan*/  AML_INT_BYTELIST_OP ; 
 int /*<<< orphan*/  AML_INT_METHODCALL_OP ; 
 int /*<<< orphan*/  AML_INT_NAMEPATH_OP ; 
#define  ARGP_BYTEDATA 145 
#define  ARGP_BYTELIST 144 
#define  ARGP_CHARLIST 143 
#define  ARGP_DATAOBJ 142 
#define  ARGP_DATAOBJLIST 141 
#define  ARGP_DWORDDATA 140 
#define  ARGP_FIELDLIST 139 
#define  ARGP_NAME 138 
#define  ARGP_NAMESTRING 137 
#define  ARGP_NAME_OR_REF 136 
#define  ARGP_OBJLIST 135 
#define  ARGP_PKGLENGTH 134 
#define  ARGP_SIMPLENAME 133 
#define  ARGP_SUPERNAME 132 
#define  ARGP_TARGET 131 
#define  ARGP_TERMARG 130 
#define  ARGP_TERMLIST 129 
#define  ARGP_WORDDATA 128 
 TYPE_6__* AcpiPsAllocOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsFreeOp (TYPE_6__*) ; 
 TYPE_6__* AcpiPsGetNextField (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiPsGetNextNamepath (TYPE_4__*,TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsGetNextPackageEnd (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiPsGetNextSimpleArg (TYPE_5__*,int,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiPsIsLeadingChar (int) ; 
 int AcpiPsPeekOpcode (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetArgumentTypeName (int) ; 
 int /*<<< orphan*/  PsGetNextArg ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiPsGetNextArg (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_STATE        *ParserState,
    UINT32                  ArgType,
    ACPI_PARSE_OBJECT       **ReturnArg)
{
    ACPI_PARSE_OBJECT       *Arg = NULL;
    ACPI_PARSE_OBJECT       *Prev = NULL;
    ACPI_PARSE_OBJECT       *Field;
    UINT32                  Subop;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE_PTR (PsGetNextArg, ParserState);


    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
        "Expected argument type ARGP: %s (%2.2X)\n",
        AcpiUtGetArgumentTypeName (ArgType), ArgType));

    switch (ArgType)
    {
    case ARGP_BYTEDATA:
    case ARGP_WORDDATA:
    case ARGP_DWORDDATA:
    case ARGP_CHARLIST:
    case ARGP_NAME:
    case ARGP_NAMESTRING:

        /* Constants, strings, and namestrings are all the same size */

        Arg = AcpiPsAllocOp (AML_BYTE_OP, ParserState->Aml);
        if (!Arg)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        AcpiPsGetNextSimpleArg (ParserState, ArgType, Arg);
        break;

    case ARGP_PKGLENGTH:

        /* Package length, nothing returned */

        ParserState->PkgEnd = AcpiPsGetNextPackageEnd (ParserState);
        break;

    case ARGP_FIELDLIST:

        if (ParserState->Aml < ParserState->PkgEnd)
        {
            /* Non-empty list */

            while (ParserState->Aml < ParserState->PkgEnd)
            {
                Field = AcpiPsGetNextField (ParserState);
                if (!Field)
                {
                    return_ACPI_STATUS (AE_NO_MEMORY);
                }

                if (Prev)
                {
                    Prev->Common.Next = Field;
                }
                else
                {
                    Arg = Field;
                }
                Prev = Field;
            }

            /* Skip to End of byte data */

            ParserState->Aml = ParserState->PkgEnd;
        }
        break;

    case ARGP_BYTELIST:

        if (ParserState->Aml < ParserState->PkgEnd)
        {
            /* Non-empty list */

            Arg = AcpiPsAllocOp (AML_INT_BYTELIST_OP,
                ParserState->Aml);
            if (!Arg)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* Fill in bytelist data */

            Arg->Common.Value.Size = (UINT32)
                ACPI_PTR_DIFF (ParserState->PkgEnd, ParserState->Aml);
            Arg->Named.Data = ParserState->Aml;

            /* Skip to End of byte data */

            ParserState->Aml = ParserState->PkgEnd;
        }
        break;

    case ARGP_SIMPLENAME:
    case ARGP_NAME_OR_REF:

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "**** SimpleName/NameOrRef: %s (%2.2X)\n",
            AcpiUtGetArgumentTypeName (ArgType), ArgType));

        Subop = AcpiPsPeekOpcode (ParserState);
        if (Subop == 0                  ||
            AcpiPsIsLeadingChar (Subop) ||
            ACPI_IS_ROOT_PREFIX (Subop) ||
            ACPI_IS_PARENT_PREFIX (Subop))
        {
            /* NullName or NameString */

            Arg = AcpiPsAllocOp (AML_INT_NAMEPATH_OP, ParserState->Aml);
            if (!Arg)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            Status = AcpiPsGetNextNamepath (WalkState, ParserState,
                Arg, ACPI_NOT_METHOD_CALL);
        }
        else
        {
            /* Single complex argument, nothing returned */

            WalkState->ArgCount = 1;
        }
        break;

    case ARGP_TARGET:
    case ARGP_SUPERNAME:

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "**** Target/Supername: %s (%2.2X)\n",
            AcpiUtGetArgumentTypeName (ArgType), ArgType));

        Subop = AcpiPsPeekOpcode (ParserState);
        if (Subop == 0                  ||
            AcpiPsIsLeadingChar (Subop) ||
            ACPI_IS_ROOT_PREFIX (Subop) ||
            ACPI_IS_PARENT_PREFIX (Subop))
        {
            /* NULL target (zero). Convert to a NULL namepath */

            Arg = AcpiPsAllocOp (AML_INT_NAMEPATH_OP, ParserState->Aml);
            if (!Arg)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            Status = AcpiPsGetNextNamepath (WalkState, ParserState,
                Arg, ACPI_POSSIBLE_METHOD_CALL);

            if (Arg->Common.AmlOpcode == AML_INT_METHODCALL_OP)
            {
                /* Free method call op and corresponding namestring sub-ob */

                AcpiPsFreeOp (Arg->Common.Value.Arg);
                AcpiPsFreeOp (Arg);
                Arg = NULL;
                WalkState->ArgCount = 1;
            }
        }
        else
        {
            /* Single complex argument, nothing returned */

            WalkState->ArgCount = 1;
        }
        break;

    case ARGP_DATAOBJ:
    case ARGP_TERMARG:

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "**** TermArg/DataObj: %s (%2.2X)\n",
            AcpiUtGetArgumentTypeName (ArgType), ArgType));

        /* Single complex argument, nothing returned */

        WalkState->ArgCount = 1;
        break;

    case ARGP_DATAOBJLIST:
    case ARGP_TERMLIST:
    case ARGP_OBJLIST:

        if (ParserState->Aml < ParserState->PkgEnd)
        {
            /* Non-empty list of variable arguments, nothing returned */

            WalkState->ArgCount = ACPI_VAR_ARGS;
        }
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Invalid ArgType: 0x%X", ArgType));
        Status = AE_AML_OPERAND_TYPE;
        break;
    }

    *ReturnArg = Arg;
    return_ACPI_STATUS (Status);
}