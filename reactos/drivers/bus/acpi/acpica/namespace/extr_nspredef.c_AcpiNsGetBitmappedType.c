#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int Type; } ;
struct TYPE_5__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RTYPE_ANY ; 
 int /*<<< orphan*/  ACPI_RTYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_RTYPE_NONE ; 
 int /*<<< orphan*/  ACPI_RTYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_RTYPE_REFERENCE ; 
 int /*<<< orphan*/  ACPI_RTYPE_STRING ; 
#define  ACPI_TYPE_BUFFER 132 
#define  ACPI_TYPE_INTEGER 131 
#define  ACPI_TYPE_LOCAL_REFERENCE 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 

__attribute__((used)) static UINT32
AcpiNsGetBitmappedType (
    ACPI_OPERAND_OBJECT         *ReturnObject)
{
    UINT32                      ReturnBtype;


    if (!ReturnObject)
    {
        return (ACPI_RTYPE_NONE);
    }

    /* Map ACPI_OBJECT_TYPE to internal bitmapped type */

    switch (ReturnObject->Common.Type)
    {
    case ACPI_TYPE_INTEGER:

        ReturnBtype = ACPI_RTYPE_INTEGER;
        break;

    case ACPI_TYPE_BUFFER:

        ReturnBtype = ACPI_RTYPE_BUFFER;
        break;

    case ACPI_TYPE_STRING:

        ReturnBtype = ACPI_RTYPE_STRING;
        break;

    case ACPI_TYPE_PACKAGE:

        ReturnBtype = ACPI_RTYPE_PACKAGE;
        break;

    case ACPI_TYPE_LOCAL_REFERENCE:

        ReturnBtype = ACPI_RTYPE_REFERENCE;
        break;

    default:

        /* Not one of the supported objects, must be incorrect */

        ReturnBtype = ACPI_RTYPE_ANY;
        break;
    }

    return (ReturnBtype);
}