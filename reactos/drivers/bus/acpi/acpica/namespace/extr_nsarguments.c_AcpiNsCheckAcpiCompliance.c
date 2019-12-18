#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_12__ {int Flags; scalar_t__ Type; TYPE_2__* Object; } ;
struct TYPE_10__ {int ArgumentList; int /*<<< orphan*/  ExpectedBtypes; } ;
struct TYPE_11__ {TYPE_3__ Info; } ;
struct TYPE_8__ {scalar_t__ ParamCount; } ;
struct TYPE_9__ {TYPE_1__ Method; } ;
typedef  TYPE_4__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_ERROR_PREDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_WARN_ALWAYS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int ANOBJ_EVALUATED ; 
 int ARG_COUNT_IS_MINIMUM ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (scalar_t__) ; 
 scalar_t__ METHOD_GET_ARG_COUNT (int) ; 

void
AcpiNsCheckAcpiCompliance (
    char                        *Pathname,
    ACPI_NAMESPACE_NODE         *Node,
    const ACPI_PREDEFINED_INFO  *Predefined)
{
    UINT32                      AmlParamCount;
    UINT32                      RequiredParamCount;


    if (!Predefined || (Node->Flags & ANOBJ_EVALUATED))
    {
        return;
    }

    /* Get the ACPI-required arg count from the predefined info table */

    RequiredParamCount =
        METHOD_GET_ARG_COUNT (Predefined->Info.ArgumentList);

    /*
     * If this object is not a control method, we can check if the ACPI
     * spec requires that it be a method.
     */
    if (Node->Type != ACPI_TYPE_METHOD)
    {
        if (RequiredParamCount > 0)
        {
            /* Object requires args, must be implemented as a method */

            ACPI_BIOS_ERROR_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Object (%s) must be a control method with %u arguments",
                AcpiUtGetTypeName (Node->Type), RequiredParamCount));
        }
        else if (!RequiredParamCount && !Predefined->Info.ExpectedBtypes)
        {
            /* Object requires no args and no return value, must be a method */

            ACPI_BIOS_ERROR_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Object (%s) must be a control method "
                "with no arguments and no return value",
                AcpiUtGetTypeName (Node->Type)));
        }

        return;
    }

    /*
     * This is a control method.
     * Check that the ASL/AML-defined parameter count for this method
     * matches the ACPI-required parameter count
     *
     * Some methods are allowed to have a "minimum" number of args (_SCP)
     * because their definition in ACPI has changed over time.
     *
     * Note: These are BIOS errors in the declaration of the object
     */
    AmlParamCount = Node->Object->Method.ParamCount;

    if (AmlParamCount < RequiredParamCount)
    {
        ACPI_BIOS_ERROR_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
            "Insufficient arguments - "
            "ASL declared %u, ACPI requires %u",
            AmlParamCount, RequiredParamCount));
    }
    else if ((AmlParamCount > RequiredParamCount) &&
        !(Predefined->Info.ArgumentList & ARG_COUNT_IS_MINIMUM))
    {
        ACPI_BIOS_ERROR_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
            "Excess arguments - "
            "ASL declared %u, ACPI requires %u",
            AmlParamCount, RequiredParamCount));
    }
}