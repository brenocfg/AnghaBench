#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_31__ {int Type; } ;
struct TYPE_30__ {scalar_t__ Class; scalar_t__ RuntimeArgs; int /*<<< orphan*/  Name; } ;
struct TYPE_27__ {int Type; } ;
struct TYPE_26__ {int const Class; } ;
struct TYPE_29__ {TYPE_2__ Common; TYPE_1__ Reference; } ;
struct TYPE_28__ {int /*<<< orphan*/  NumOperands; int /*<<< orphan*/  Operands; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_OPCODE_INFO ;
typedef  int ACPI_OBJECT_TYPE ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_DESC_TYPE_NAMED 170 
#define  ACPI_DESC_TYPE_OPERAND 169 
 int /*<<< orphan*/  ACPI_DUMP_OPERANDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const ACPI_GET_DESCRIPTOR_TYPE (TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERSION ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERT_HEX ; 
#define  ACPI_REFCLASS_ARG 168 
#define  ACPI_REFCLASS_DEBUG 167 
#define  ACPI_REFCLASS_INDEX 166 
#define  ACPI_REFCLASS_LOCAL 165 
#define  ACPI_REFCLASS_NAME 164 
#define  ACPI_REFCLASS_REFOF 163 
#define  ACPI_REFCLASS_TABLE 162 
 int ACPI_TYPE_ANY ; 
#define  ACPI_TYPE_BUFFER 161 
#define  ACPI_TYPE_BUFFER_FIELD 160 
#define  ACPI_TYPE_DDB_HANDLE 159 
 int ACPI_TYPE_EVENT ; 
#define  ACPI_TYPE_INTEGER 158 
 int ACPI_TYPE_LOCAL_ALIAS ; 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 157 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 156 
#define  ACPI_TYPE_LOCAL_REFERENCE 155 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 154 
 int ACPI_TYPE_MUTEX ; 
#define  ACPI_TYPE_PACKAGE 153 
#define  ACPI_TYPE_REGION 152 
#define  ACPI_TYPE_STRING 151 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 scalar_t__ AML_CLASS_UNKNOWN ; 
 int /*<<< orphan*/  AML_DEBUG_OP ; 
 int /*<<< orphan*/  AML_STORE_OP ; 
#define  ARGI_ANYTYPE 150 
#define  ARGI_BUFFER 149 
#define  ARGI_BUFFER_OR_STRING 148 
#define  ARGI_COMPLEXOBJ 147 
#define  ARGI_COMPUTEDATA 146 
#define  ARGI_DATAOBJECT 145 
#define  ARGI_DATAREFOBJ 144 
#define  ARGI_DDBHANDLE 143 
#define  ARGI_DEVICE_REF 142 
#define  ARGI_EVENT 141 
#define  ARGI_FIXED_TARGET 140 
#define  ARGI_INTEGER 139 
#define  ARGI_INTEGER_REF 138 
 scalar_t__ ARGI_INVALID_OPCODE ; 
#define  ARGI_MUTEX 137 
#define  ARGI_OBJECT_REF 136 
#define  ARGI_PACKAGE 135 
#define  ARGI_REFERENCE 134 
#define  ARGI_REF_OR_STRING 133 
#define  ARGI_REGION_OR_BUFFER 132 
#define  ARGI_SIMPLE_TARGET 131 
#define  ARGI_STORE_TARGET 130 
#define  ARGI_STRING 129 
#define  ARGI_TARGETREF 128 
 int /*<<< orphan*/  AcpiExCheckObjectType (int,int,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiExConvertToBuffer (TYPE_4__*,TYPE_4__**) ; 
 int /*<<< orphan*/  AcpiExConvertToInteger (TYPE_4__*,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExConvertToString (TYPE_4__*,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExResolveToValue (TYPE_4__**,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiGbl_EnableInterpreterSlack ; 
 TYPE_4__* AcpiNsGetAttachedObject (TYPE_6__*) ; 
 TYPE_5__* AcpiPsGetOpcodeInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorName (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtGetReferenceName (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtValidObjectType (int) ; 
 int /*<<< orphan*/  ExResolveOperands ; 
 scalar_t__ GET_CURRENT_ARG_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  INCREMENT_ARG_LIST (scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExResolveOperands (
    UINT16                  Opcode,
    ACPI_OPERAND_OBJECT     **StackPtr,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status = AE_OK;
    UINT8                   ObjectType;
    UINT32                  ArgTypes;
    const ACPI_OPCODE_INFO  *OpInfo;
    UINT32                  ThisArgType;
    ACPI_OBJECT_TYPE        TypeNeeded;
    UINT16                  TargetOp = 0;


    ACPI_FUNCTION_TRACE_U32 (ExResolveOperands, Opcode);


    OpInfo = AcpiPsGetOpcodeInfo (Opcode);
    if (OpInfo->Class == AML_CLASS_UNKNOWN)
    {
        return_ACPI_STATUS (AE_AML_BAD_OPCODE);
    }

    ArgTypes = OpInfo->RuntimeArgs;
    if (ArgTypes == ARGI_INVALID_OPCODE)
    {
        ACPI_ERROR ((AE_INFO, "Unknown AML opcode 0x%X",
            Opcode));

        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Opcode %X [%s] RequiredOperandTypes=%8.8X\n",
        Opcode, OpInfo->Name, ArgTypes));

    /*
     * Normal exit is with (ArgTypes == 0) at end of argument list.
     * Function will return an exception from within the loop upon
     * finding an entry which is not (or cannot be converted
     * to) the required type; if stack underflows; or upon
     * finding a NULL stack entry (which should not happen).
     */
    while (GET_CURRENT_ARG_TYPE (ArgTypes))
    {
        if (!StackPtr || !*StackPtr)
        {
            ACPI_ERROR ((AE_INFO, "Null stack entry at %p",
                StackPtr));

            return_ACPI_STATUS (AE_AML_INTERNAL);
        }

        /* Extract useful items */

        ObjDesc = *StackPtr;

        /* Decode the descriptor type */

        switch (ACPI_GET_DESCRIPTOR_TYPE (ObjDesc))
        {
        case ACPI_DESC_TYPE_NAMED:

            /* Namespace Node */

            ObjectType = ((ACPI_NAMESPACE_NODE *) ObjDesc)->Type;

            /*
             * Resolve an alias object. The construction of these objects
             * guarantees that there is only one level of alias indirection;
             * thus, the attached object is always the aliased namespace node
             */
            if (ObjectType == ACPI_TYPE_LOCAL_ALIAS)
            {
                ObjDesc = AcpiNsGetAttachedObject (
                    (ACPI_NAMESPACE_NODE *) ObjDesc);
                *StackPtr = ObjDesc;
                ObjectType = ((ACPI_NAMESPACE_NODE *) ObjDesc)->Type;
            }
            break;

        case ACPI_DESC_TYPE_OPERAND:

            /* ACPI internal object */

            ObjectType = ObjDesc->Common.Type;

            /* Check for bad ACPI_OBJECT_TYPE */

            if (!AcpiUtValidObjectType (ObjectType))
            {
                ACPI_ERROR ((AE_INFO,
                    "Bad operand object type [0x%X]", ObjectType));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }

            if (ObjectType == (UINT8) ACPI_TYPE_LOCAL_REFERENCE)
            {
                /* Validate the Reference */

                switch (ObjDesc->Reference.Class)
                {
                case ACPI_REFCLASS_DEBUG:

                    TargetOp = AML_DEBUG_OP;

                    /*lint -fallthrough */

                case ACPI_REFCLASS_ARG:
                case ACPI_REFCLASS_LOCAL:
                case ACPI_REFCLASS_INDEX:
                case ACPI_REFCLASS_REFOF:
                case ACPI_REFCLASS_TABLE:    /* DdbHandle from LOAD_OP or LOAD_TABLE_OP */
                case ACPI_REFCLASS_NAME:     /* Reference to a named object */

                    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
                        "Operand is a Reference, Class [%s] %2.2X\n",
                        AcpiUtGetReferenceName (ObjDesc),
                        ObjDesc->Reference.Class));
                    break;

                default:

                    ACPI_ERROR ((AE_INFO,
                        "Unknown Reference Class 0x%2.2X in %p",
                        ObjDesc->Reference.Class, ObjDesc));

                    return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
                }
            }
            break;

        default:

            /* Invalid descriptor */

            ACPI_ERROR ((AE_INFO, "Invalid descriptor %p [%s]",
                ObjDesc, AcpiUtGetDescriptorName (ObjDesc)));

            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        /* Get one argument type, point to the next */

        ThisArgType = GET_CURRENT_ARG_TYPE (ArgTypes);
        INCREMENT_ARG_LIST (ArgTypes);

        /*
         * Handle cases where the object does not need to be
         * resolved to a value
         */
        switch (ThisArgType)
        {
        case ARGI_REF_OR_STRING:        /* Can be a String or Reference */

            if ((ACPI_GET_DESCRIPTOR_TYPE (ObjDesc) ==
                ACPI_DESC_TYPE_OPERAND) &&
                (ObjDesc->Common.Type == ACPI_TYPE_STRING))
            {
                /*
                 * String found - the string references a named object and
                 * must be resolved to a node
                 */
                goto NextOperand;
            }

            /*
             * Else not a string - fall through to the normal Reference
             * case below
             */
            /*lint -fallthrough */

        case ARGI_REFERENCE:            /* References: */
        case ARGI_INTEGER_REF:
        case ARGI_OBJECT_REF:
        case ARGI_DEVICE_REF:
        case ARGI_TARGETREF:     /* Allows implicit conversion rules before store */
        case ARGI_FIXED_TARGET:  /* No implicit conversion before store to target */
        case ARGI_SIMPLE_TARGET: /* Name, Local, or Arg - no implicit conversion  */
        case ARGI_STORE_TARGET:

            /*
             * Need an operand of type ACPI_TYPE_LOCAL_REFERENCE
             * A Namespace Node is OK as-is
             */
            if (ACPI_GET_DESCRIPTOR_TYPE (ObjDesc) == ACPI_DESC_TYPE_NAMED)
            {
                goto NextOperand;
            }

            Status = AcpiExCheckObjectType (
                ACPI_TYPE_LOCAL_REFERENCE, ObjectType, ObjDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
            goto NextOperand;

        case ARGI_DATAREFOBJ:  /* Store operator only */
            /*
             * We don't want to resolve IndexOp reference objects during
             * a store because this would be an implicit DeRefOf operation.
             * Instead, we just want to store the reference object.
             * -- All others must be resolved below.
             */
            if ((Opcode == AML_STORE_OP) &&
                ((*StackPtr)->Common.Type == ACPI_TYPE_LOCAL_REFERENCE) &&
                ((*StackPtr)->Reference.Class == ACPI_REFCLASS_INDEX))
            {
                goto NextOperand;
            }
            break;

        default:

            /* All cases covered above */

            break;
        }

        /*
         * Resolve this object to a value
         */
        Status = AcpiExResolveToValue (StackPtr, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* Get the resolved object */

        ObjDesc = *StackPtr;

        /*
         * Check the resulting object (value) type
         */
        switch (ThisArgType)
        {
        /*
         * For the simple cases, only one type of resolved object
         * is allowed
         */
        case ARGI_MUTEX:

            /* Need an operand of type ACPI_TYPE_MUTEX */

            TypeNeeded = ACPI_TYPE_MUTEX;
            break;

        case ARGI_EVENT:

            /* Need an operand of type ACPI_TYPE_EVENT */

            TypeNeeded = ACPI_TYPE_EVENT;
            break;

        case ARGI_PACKAGE:   /* Package */

            /* Need an operand of type ACPI_TYPE_PACKAGE */

            TypeNeeded = ACPI_TYPE_PACKAGE;
            break;

        case ARGI_ANYTYPE:

            /* Any operand type will do */

            TypeNeeded = ACPI_TYPE_ANY;
            break;

        case ARGI_DDBHANDLE:

            /* Need an operand of type ACPI_TYPE_DDB_HANDLE */

            TypeNeeded = ACPI_TYPE_LOCAL_REFERENCE;
            break;


        /*
         * The more complex cases allow multiple resolved object types
         */
        case ARGI_INTEGER:

            /*
             * Need an operand of type ACPI_TYPE_INTEGER, but we can
             * implicitly convert from a STRING or BUFFER.
             *
             * Known as "Implicit Source Operand Conversion"
             */
            Status = AcpiExConvertToInteger (ObjDesc, StackPtr,
                ACPI_IMPLICIT_CONVERSION);
            if (ACPI_FAILURE (Status))
            {
                if (Status == AE_TYPE)
                {
                    ACPI_ERROR ((AE_INFO,
                        "Needed [Integer/String/Buffer], found [%s] %p",
                        AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                    return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
                }

                return_ACPI_STATUS (Status);
            }

            if (ObjDesc != *StackPtr)
            {
                AcpiUtRemoveReference (ObjDesc);
            }
            goto NextOperand;

        case ARGI_BUFFER:
            /*
             * Need an operand of type ACPI_TYPE_BUFFER,
             * But we can implicitly convert from a STRING or INTEGER
             * Aka - "Implicit Source Operand Conversion"
             */
            Status = AcpiExConvertToBuffer (ObjDesc, StackPtr);
            if (ACPI_FAILURE (Status))
            {
                if (Status == AE_TYPE)
                {
                    ACPI_ERROR ((AE_INFO,
                        "Needed [Integer/String/Buffer], found [%s] %p",
                        AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                    return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
                }

                return_ACPI_STATUS (Status);
            }

            if (ObjDesc != *StackPtr)
            {
                AcpiUtRemoveReference (ObjDesc);
            }
            goto NextOperand;

        case ARGI_STRING:
            /*
             * Need an operand of type ACPI_TYPE_STRING,
             * But we can implicitly convert from a BUFFER or INTEGER
             * Aka - "Implicit Source Operand Conversion"
             */
            Status = AcpiExConvertToString (
                ObjDesc, StackPtr, ACPI_IMPLICIT_CONVERT_HEX);
            if (ACPI_FAILURE (Status))
            {
                if (Status == AE_TYPE)
                {
                    ACPI_ERROR ((AE_INFO,
                        "Needed [Integer/String/Buffer], found [%s] %p",
                        AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                    return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
                }

                return_ACPI_STATUS (Status);
            }

            if (ObjDesc != *StackPtr)
            {
                AcpiUtRemoveReference (ObjDesc);
            }
            goto NextOperand;

        case ARGI_COMPUTEDATA:

            /* Need an operand of type INTEGER, STRING or BUFFER */

            switch (ObjDesc->Common.Type)
            {
            case ACPI_TYPE_INTEGER:
            case ACPI_TYPE_STRING:
            case ACPI_TYPE_BUFFER:

                /* Valid operand */
               break;

            default:
                ACPI_ERROR ((AE_INFO,
                    "Needed [Integer/String/Buffer], found [%s] %p",
                    AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }
            goto NextOperand;

        case ARGI_BUFFER_OR_STRING:

            /* Need an operand of type STRING or BUFFER */

            switch (ObjDesc->Common.Type)
            {
            case ACPI_TYPE_STRING:
            case ACPI_TYPE_BUFFER:

                /* Valid operand */
               break;

            case ACPI_TYPE_INTEGER:

                /* Highest priority conversion is to type Buffer */

                Status = AcpiExConvertToBuffer (ObjDesc, StackPtr);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }

                if (ObjDesc != *StackPtr)
                {
                    AcpiUtRemoveReference (ObjDesc);
                }
                break;

            default:
                ACPI_ERROR ((AE_INFO,
                    "Needed [Integer/String/Buffer], found [%s] %p",
                    AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }
            goto NextOperand;

        case ARGI_DATAOBJECT:
            /*
             * ARGI_DATAOBJECT is only used by the SizeOf operator.
             * Need a buffer, string, package, or RefOf reference.
             *
             * The only reference allowed here is a direct reference to
             * a namespace node.
             */
            switch (ObjDesc->Common.Type)
            {
            case ACPI_TYPE_PACKAGE:
            case ACPI_TYPE_STRING:
            case ACPI_TYPE_BUFFER:
            case ACPI_TYPE_LOCAL_REFERENCE:

                /* Valid operand */
                break;

            default:

                ACPI_ERROR ((AE_INFO,
                    "Needed [Buffer/String/Package/Reference], found [%s] %p",
                    AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }
            goto NextOperand;

        case ARGI_COMPLEXOBJ:

            /* Need a buffer or package or (ACPI 2.0) String */

            switch (ObjDesc->Common.Type)
            {
            case ACPI_TYPE_PACKAGE:
            case ACPI_TYPE_STRING:
            case ACPI_TYPE_BUFFER:

                /* Valid operand */
                break;

            default:

                ACPI_ERROR ((AE_INFO,
                    "Needed [Buffer/String/Package], found [%s] %p",
                    AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }
            goto NextOperand;

        case ARGI_REGION_OR_BUFFER: /* Used by Load() only */

            /*
             * Need an operand of type REGION or a BUFFER
             * (which could be a resolved region field)
             */
            switch (ObjDesc->Common.Type)
            {
            case ACPI_TYPE_BUFFER:
            case ACPI_TYPE_REGION:

                /* Valid operand */
                break;

            default:

                ACPI_ERROR ((AE_INFO,
                    "Needed [Region/Buffer], found [%s] %p",
                    AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }
            goto NextOperand;

        case ARGI_DATAREFOBJ:

            /* Used by the Store() operator only */

            switch (ObjDesc->Common.Type)
            {
            case ACPI_TYPE_INTEGER:
            case ACPI_TYPE_PACKAGE:
            case ACPI_TYPE_STRING:
            case ACPI_TYPE_BUFFER:
            case ACPI_TYPE_BUFFER_FIELD:
            case ACPI_TYPE_LOCAL_REFERENCE:
            case ACPI_TYPE_LOCAL_REGION_FIELD:
            case ACPI_TYPE_LOCAL_BANK_FIELD:
            case ACPI_TYPE_LOCAL_INDEX_FIELD:
            case ACPI_TYPE_DDB_HANDLE:

                /* Valid operand */
                break;

            default:

                if (AcpiGbl_EnableInterpreterSlack)
                {
                    /*
                     * Enable original behavior of Store(), allowing any
                     * and all objects as the source operand. The ACPI
                     * spec does not allow this, however.
                     */
                    break;
                }

                if (TargetOp == AML_DEBUG_OP)
                {
                    /* Allow store of any object to the Debug object */

                    break;
                }

                ACPI_ERROR ((AE_INFO,
                    "Needed Integer/Buffer/String/Package/Ref/Ddb]"
                    ", found [%s] %p",
                    AcpiUtGetObjectTypeName (ObjDesc), ObjDesc));

                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }
            goto NextOperand;

        default:

            /* Unknown type */

            ACPI_ERROR ((AE_INFO,
                "Internal - Unknown ARGI (required operand) type 0x%X",
                ThisArgType));

            return_ACPI_STATUS (AE_BAD_PARAMETER);
        }

        /*
         * Make sure that the original object was resolved to the
         * required object type (Simple cases only).
         */
        Status = AcpiExCheckObjectType (
            TypeNeeded, (*StackPtr)->Common.Type, *StackPtr);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

NextOperand:
        /*
         * If more operands needed, decrement StackPtr to point
         * to next operand on stack
         */
        if (GET_CURRENT_ARG_TYPE (ArgTypes))
        {
            StackPtr--;
        }
    }

    ACPI_DUMP_OPERANDS (WalkState->Operands,
        AcpiPsGetOpcodeName (Opcode), WalkState->NumOperands);

    return_ACPI_STATUS (Status);
}