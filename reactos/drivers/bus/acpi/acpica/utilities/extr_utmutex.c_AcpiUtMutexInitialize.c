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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  AcpiGbl_GpeLock ; 
 int /*<<< orphan*/  AcpiGbl_HardwareLock ; 
 int /*<<< orphan*/  AcpiGbl_NamespaceRwLock ; 
 int /*<<< orphan*/  AcpiGbl_OsiMutex ; 
 int /*<<< orphan*/  AcpiGbl_ReferenceCountLock ; 
 int /*<<< orphan*/  AcpiOsCreateLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsCreateMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtCreateMutex (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtCreateRwLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtMutexInitialize ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtMutexInitialize (
    void)
{
    UINT32                  i;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (UtMutexInitialize);


    /* Create each of the predefined mutex objects */

    for (i = 0; i < ACPI_NUM_MUTEX; i++)
    {
        Status = AcpiUtCreateMutex (i);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* Create the spinlocks for use at interrupt level or for speed */

    Status = AcpiOsCreateLock (&AcpiGbl_GpeLock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AcpiOsCreateLock (&AcpiGbl_HardwareLock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AcpiOsCreateLock (&AcpiGbl_ReferenceCountLock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Mutex for _OSI support */

    Status = AcpiOsCreateMutex (&AcpiGbl_OsiMutex);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Create the reader/writer lock for namespace access */

    Status = AcpiUtCreateRwLock (&AcpiGbl_NamespaceRwLock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    return_ACPI_STATUS (Status);
}