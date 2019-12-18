#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Length; int /*<<< orphan*/  Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE (int) ; 
#define  ACPI_ALLOCATE_BUFFER 130 
#define  ACPI_ALLOCATE_LOCAL_BUFFER 129 
#define  ACPI_NO_BUFFER 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiOsAllocate (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

ACPI_STATUS
AcpiUtInitializeBuffer (
    ACPI_BUFFER             *Buffer,
    ACPI_SIZE               RequiredLength)
{
    ACPI_SIZE               InputBufferLength;


    /* Parameter validation */

    if (!Buffer || !RequiredLength)
    {
        return (AE_BAD_PARAMETER);
    }

    /*
     * Buffer->Length is used as both an input and output parameter. Get the
     * input actual length and set the output required buffer length.
     */
    InputBufferLength = Buffer->Length;
    Buffer->Length = RequiredLength;

    /*
     * The input buffer length contains the actual buffer length, or the type
     * of buffer to be allocated by this routine.
     */
    switch (InputBufferLength)
    {
    case ACPI_NO_BUFFER:

        /* Return the exception (and the required buffer length) */

        return (AE_BUFFER_OVERFLOW);

    case ACPI_ALLOCATE_BUFFER:
        /*
         * Allocate a new buffer. We directectly call AcpiOsAllocate here to
         * purposefully bypass the (optionally enabled) internal allocation
         * tracking mechanism since we only want to track internal
         * allocations. Note: The caller should use AcpiOsFree to free this
         * buffer created via ACPI_ALLOCATE_BUFFER.
         */
        Buffer->Pointer = AcpiOsAllocate (RequiredLength);
        break;

    case ACPI_ALLOCATE_LOCAL_BUFFER:

        /* Allocate a new buffer with local interface to allow tracking */

        Buffer->Pointer = ACPI_ALLOCATE (RequiredLength);
        break;

    default:

        /* Existing buffer: Validate the size of the buffer */

        if (InputBufferLength < RequiredLength)
        {
            return (AE_BUFFER_OVERFLOW);
        }
        break;
    }

    /* Validate allocation from above or input buffer pointer */

    if (!Buffer->Pointer)
    {
        return (AE_NO_MEMORY);
    }

    /* Have a valid buffer, clear it */

    memset (Buffer->Pointer, 0, RequiredLength);
    return (AE_OK);
}