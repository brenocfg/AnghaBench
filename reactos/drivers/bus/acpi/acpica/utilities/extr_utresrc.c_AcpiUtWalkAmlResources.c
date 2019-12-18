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
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  AML_RESOURCE_END_TAG ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  (* ACPI_WALK_AML_CALLBACK ) (int*,int,int,int,void**) ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_RESOURCE_NAME_END_TAG ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AE_OK ; 
 int AcpiUtGetDescriptorLength (int*) ; 
 scalar_t__ AcpiUtGetResourceType (int*) ; 
 int /*<<< orphan*/  AcpiUtValidateResource (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  UtWalkAmlResources ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtWalkAmlResources (
    ACPI_WALK_STATE         *WalkState,
    UINT8                   *Aml,
    ACPI_SIZE               AmlLength,
    ACPI_WALK_AML_CALLBACK  UserFunction,
    void                    **Context)
{
    ACPI_STATUS             Status;
    UINT8                   *EndAml;
    UINT8                   ResourceIndex;
    UINT32                  Length;
    UINT32                  Offset = 0;
    UINT8                   EndTag[2] = {0x79, 0x00};


    ACPI_FUNCTION_TRACE (UtWalkAmlResources);


    /* The absolute minimum resource template is one EndTag descriptor */

    if (AmlLength < sizeof (AML_RESOURCE_END_TAG))
    {
        return_ACPI_STATUS (AE_AML_NO_RESOURCE_END_TAG);
    }

    /* Point to the end of the resource template buffer */

    EndAml = Aml + AmlLength;

    /* Walk the byte list, abort on any invalid descriptor type or length */

    while (Aml < EndAml)
    {
        /* Validate the Resource Type and Resource Length */

        Status = AcpiUtValidateResource (WalkState, Aml, &ResourceIndex);
        if (ACPI_FAILURE (Status))
        {
            /*
             * Exit on failure. Cannot continue because the descriptor
             * length may be bogus also.
             */
            return_ACPI_STATUS (Status);
        }

        /* Get the length of this descriptor */

        Length = AcpiUtGetDescriptorLength (Aml);

        /* Invoke the user function */

        if (UserFunction)
        {
            Status = UserFunction (
                Aml, Length, Offset, ResourceIndex, Context);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
        }

        /* An EndTag descriptor terminates this resource template */

        if (AcpiUtGetResourceType (Aml) == ACPI_RESOURCE_NAME_END_TAG)
        {
            /*
             * There must be at least one more byte in the buffer for
             * the 2nd byte of the EndTag
             */
            if ((Aml + 1) >= EndAml)
            {
                return_ACPI_STATUS (AE_AML_NO_RESOURCE_END_TAG);
            }

            /*
             * Don't attempt to perform any validation on the 2nd byte.
             * Although all known ASL compilers insert a zero for the 2nd
             * byte, it can also be a checksum (as per the ACPI spec),
             * and this is occasionally seen in the field. July 2017.
             */

            /* Return the pointer to the EndTag if requested */

            if (!UserFunction)
            {
                *Context = Aml;
            }

            /* Normal exit */

            return_ACPI_STATUS (AE_OK);
        }

        Aml += Length;
        Offset += Length;
    }

    /* Did not find an EndTag descriptor */

    if (UserFunction)
    {
        /* Insert an EndTag anyway. AcpiRsGetListLength always leaves room */

        (void) AcpiUtValidateResource (WalkState, EndTag, &ResourceIndex);
        Status = UserFunction (EndTag, 2, Offset, ResourceIndex, Context);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    return_ACPI_STATUS (AE_AML_NO_RESOURCE_END_TAG);
}