#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_18__ {int /*<<< orphan*/  AccessByteWidth; } ;
struct TYPE_17__ {int Type; int Flags; } ;
struct TYPE_16__ {scalar_t__ Value; int /*<<< orphan*/  DataObj; int /*<<< orphan*/  IndexObj; } ;
struct TYPE_15__ {scalar_t__ Value; int /*<<< orphan*/  BankObj; } ;
struct TYPE_14__ {scalar_t__ BaseByteOffset; TYPE_2__* BufferObj; } ;
struct TYPE_19__ {TYPE_7__ CommonField; TYPE_6__ Common; TYPE_5__ IndexField; TYPE_4__ BankField; TYPE_3__ BufferField; } ;
struct TYPE_12__ {scalar_t__ Pointer; } ;
struct TYPE_13__ {TYPE_1__ Buffer; } ;
typedef  int /*<<< orphan*/  FieldDatumByteOffset ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_8__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ACPI_READ ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER_FIELD 131 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 130 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 129 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 128 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_REGISTER_LIMIT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsGetBufferFieldArguments (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiExAccessRegion (TYPE_8__*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  AcpiExExtractFromField (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  AcpiExInsertIntoField (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  AcpiExRegisterOverflow (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ExFieldDatumIo ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExFieldDatumIo (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  FieldDatumByteOffset,
    UINT64                  *Value,
    UINT32                  ReadWrite)
{
    ACPI_STATUS             Status;
    UINT64                  LocalValue;


    ACPI_FUNCTION_TRACE_U32 (ExFieldDatumIo, FieldDatumByteOffset);


    if (ReadWrite == ACPI_READ)
    {
        if (!Value)
        {
            LocalValue = 0;

            /* To support reads without saving return value */
            Value = &LocalValue;
        }

        /* Clear the entire return buffer first, [Very Important!] */

        *Value = 0;
    }

    /*
     * The four types of fields are:
     *
     * BufferField - Read/write from/to a Buffer
     * RegionField - Read/write from/to a Operation Region.
     * BankField   - Write to a Bank Register, then read/write from/to an
     *               OperationRegion
     * IndexField  - Write to an Index Register, then read/write from/to a
     *               Data Register
     */
    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_BUFFER_FIELD:
        /*
         * If the BufferField arguments have not been previously evaluated,
         * evaluate them now and save the results.
         */
        if (!(ObjDesc->Common.Flags & AOPOBJ_DATA_VALID))
        {
            Status = AcpiDsGetBufferFieldArguments (ObjDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
        }

        if (ReadWrite == ACPI_READ)
        {
            /*
             * Copy the data from the source buffer.
             * Length is the field width in bytes.
             */
            memcpy (Value,
                (ObjDesc->BufferField.BufferObj)->Buffer.Pointer +
                    ObjDesc->BufferField.BaseByteOffset +
                    FieldDatumByteOffset,
                ObjDesc->CommonField.AccessByteWidth);
        }
        else
        {
            /*
             * Copy the data to the target buffer.
             * Length is the field width in bytes.
             */
            memcpy ((ObjDesc->BufferField.BufferObj)->Buffer.Pointer +
                ObjDesc->BufferField.BaseByteOffset +
                FieldDatumByteOffset,
                Value, ObjDesc->CommonField.AccessByteWidth);
        }

        Status = AE_OK;
        break;

    case ACPI_TYPE_LOCAL_BANK_FIELD:
        /*
         * Ensure that the BankValue is not beyond the capacity of
         * the register
         */
        if (AcpiExRegisterOverflow (ObjDesc->BankField.BankObj,
                (UINT64) ObjDesc->BankField.Value))
        {
            return_ACPI_STATUS (AE_AML_REGISTER_LIMIT);
        }

        /*
         * For BankFields, we must write the BankValue to the BankRegister
         * (itself a RegionField) before we can access the data.
         */
        Status = AcpiExInsertIntoField (ObjDesc->BankField.BankObj,
                    &ObjDesc->BankField.Value,
                    sizeof (ObjDesc->BankField.Value));
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /*
         * Now that the Bank has been selected, fall through to the
         * RegionField case and write the datum to the Operation Region
         */

        /*lint -fallthrough */

    case ACPI_TYPE_LOCAL_REGION_FIELD:
        /*
         * For simple RegionFields, we just directly access the owning
         * Operation Region.
         */
        Status = AcpiExAccessRegion (
            ObjDesc, FieldDatumByteOffset, Value, ReadWrite);
        break;

    case ACPI_TYPE_LOCAL_INDEX_FIELD:
        /*
         * Ensure that the IndexValue is not beyond the capacity of
         * the register
         */
        if (AcpiExRegisterOverflow (ObjDesc->IndexField.IndexObj,
                (UINT64) ObjDesc->IndexField.Value))
        {
            return_ACPI_STATUS (AE_AML_REGISTER_LIMIT);
        }

        /* Write the index value to the IndexRegister (itself a RegionField) */

        FieldDatumByteOffset += ObjDesc->IndexField.Value;

        ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
            "Write to Index Register: Value %8.8X\n",
            FieldDatumByteOffset));

        Status = AcpiExInsertIntoField (ObjDesc->IndexField.IndexObj,
            &FieldDatumByteOffset, sizeof (FieldDatumByteOffset));
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        if (ReadWrite == ACPI_READ)
        {
            /* Read the datum from the DataRegister */

            ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
                "Read from Data Register\n"));

            Status = AcpiExExtractFromField (
                ObjDesc->IndexField.DataObj, Value, sizeof (UINT64));
        }
        else
        {
            /* Write the datum to the DataRegister */

            ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
                "Write to Data Register: Value %8.8X%8.8X\n",
                ACPI_FORMAT_UINT64 (*Value)));

            Status = AcpiExInsertIntoField (
                ObjDesc->IndexField.DataObj, Value, sizeof (UINT64));
        }
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Wrong object type in field I/O %u",
            ObjDesc->Common.Type));
        Status = AE_AML_INTERNAL;
        break;
    }

    if (ACPI_SUCCESS (Status))
    {
        if (ReadWrite == ACPI_READ)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
                "Value Read %8.8X%8.8X, Width %u\n",
                ACPI_FORMAT_UINT64 (*Value),
                ObjDesc->CommonField.AccessByteWidth));
        }
        else
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
                "Value Written %8.8X%8.8X, Width %u\n",
                ACPI_FORMAT_UINT64 (*Value),
                ObjDesc->CommonField.AccessByteWidth));
        }
    }

    return_ACPI_STATUS (Status);
}