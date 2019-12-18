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
struct TYPE_3__ {int Type; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
#define  ACPI_TYPE_DEVICE 130 
#define  ACPI_TYPE_PROCESSOR 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AcpiEvIsNotifyObject (
    ACPI_NAMESPACE_NODE     *Node)
{

    switch (Node->Type)
    {
    case ACPI_TYPE_DEVICE:
    case ACPI_TYPE_PROCESSOR:
    case ACPI_TYPE_THERMAL:
        /*
         * These are the ONLY objects that can receive ACPI notifications
         */
        return (TRUE);

    default:

        return (FALSE);
    }
}