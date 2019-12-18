#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {int FieldFlags; int AccessByteWidth; } ;
struct TYPE_6__ {TYPE_1__ CommonField; } ;
typedef  int /*<<< orphan*/  Mask ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ACPI_MUL_8 (int) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 scalar_t__ ACPI_UINT64_MAX ; 
 int /*<<< orphan*/  ACPI_WRITE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_FIELD_UPDATE_PRESERVE 130 
 int AML_FIELD_UPDATE_RULE_MASK ; 
#define  AML_FIELD_UPDATE_WRITE_AS_ONES 129 
#define  AML_FIELD_UPDATE_WRITE_AS_ZEROS 128 
 int /*<<< orphan*/  AcpiExFieldDatumIo (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExWriteWithUpdateRule ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExWriteWithUpdateRule (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT64                  Mask,
    UINT64                  FieldValue,
    UINT32                  FieldDatumByteOffset)
{
    ACPI_STATUS             Status = AE_OK;
    UINT64                  MergedValue;
    UINT64                  CurrentValue;


    ACPI_FUNCTION_TRACE_U32 (ExWriteWithUpdateRule, Mask);


    /* Start with the new bits  */

    MergedValue = FieldValue;

    /* If the mask is all ones, we don't need to worry about the update rule */

    if (Mask != ACPI_UINT64_MAX)
    {
        /* Decode the update rule */

        switch (ObjDesc->CommonField.FieldFlags & AML_FIELD_UPDATE_RULE_MASK)
        {
        case AML_FIELD_UPDATE_PRESERVE:
            /*
             * Check if update rule needs to be applied (not if mask is all
             * ones)  The left shift drops the bits we want to ignore.
             */
            if ((~Mask << (ACPI_MUL_8 (sizeof (Mask)) -
                   ACPI_MUL_8 (ObjDesc->CommonField.AccessByteWidth))) != 0)
            {
                /*
                 * Read the current contents of the byte/word/dword containing
                 * the field, and merge with the new field value.
                 */
                Status = AcpiExFieldDatumIo (
                    ObjDesc, FieldDatumByteOffset, &CurrentValue, ACPI_READ);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }

                MergedValue |= (CurrentValue & ~Mask);
            }
            break;

        case AML_FIELD_UPDATE_WRITE_AS_ONES:

            /* Set positions outside the field to all ones */

            MergedValue |= ~Mask;
            break;

        case AML_FIELD_UPDATE_WRITE_AS_ZEROS:

            /* Set positions outside the field to all zeros */

            MergedValue &= Mask;
            break;

        default:

            ACPI_ERROR ((AE_INFO,
                "Unknown UpdateRule value: 0x%X",
                (ObjDesc->CommonField.FieldFlags &
                    AML_FIELD_UPDATE_RULE_MASK)));
            return_ACPI_STATUS (AE_AML_OPERAND_VALUE);
        }
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
        "Mask %8.8X%8.8X, DatumOffset %X, Width %X, "
        "Value %8.8X%8.8X, MergedValue %8.8X%8.8X\n",
        ACPI_FORMAT_UINT64 (Mask),
        FieldDatumByteOffset,
        ObjDesc->CommonField.AccessByteWidth,
        ACPI_FORMAT_UINT64 (FieldValue),
        ACPI_FORMAT_UINT64 (MergedValue)));

    /* Write the merged value */

    Status = AcpiExFieldDatumIo (
        ObjDesc, FieldDatumByteOffset, &MergedValue, ACPI_WRITE);

    return_ACPI_STATUS (Status);
}