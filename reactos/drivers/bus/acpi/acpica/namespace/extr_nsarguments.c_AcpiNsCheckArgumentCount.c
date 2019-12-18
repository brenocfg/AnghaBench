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
struct TYPE_10__ {int ArgumentList; } ;
struct TYPE_11__ {TYPE_3__ Info; } ;
struct TYPE_8__ {scalar_t__ ParamCount; } ;
struct TYPE_9__ {TYPE_1__ Method; } ;
typedef  TYPE_4__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_INFO_PREDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_WARN_ALWAYS ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int ANOBJ_EVALUATED ; 
 int ARG_COUNT_IS_MINIMUM ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (scalar_t__) ; 
 scalar_t__ METHOD_GET_ARG_COUNT (int) ; 

void
AcpiNsCheckArgumentCount (
    char                        *Pathname,
    ACPI_NAMESPACE_NODE         *Node,
    UINT32                      UserParamCount,
    const ACPI_PREDEFINED_INFO  *Predefined)
{
    UINT32                      AmlParamCount;
    UINT32                      RequiredParamCount;


    if (Node->Flags & ANOBJ_EVALUATED)
    {
        return;
    }

    if (!Predefined)
    {
        /*
         * Not a predefined name. Check the incoming user argument count
         * against the count that is specified in the method/object.
         */
        if (Node->Type != ACPI_TYPE_METHOD)
        {
            if (UserParamCount)
            {
                ACPI_INFO_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                    "%u arguments were passed to a non-method ACPI object (%s)",
                    UserParamCount, AcpiUtGetTypeName (Node->Type)));
            }

            return;
        }

        /*
         * This is a control method. Check the parameter count.
         * We can only check the incoming argument count against the
         * argument count declared for the method in the ASL/AML.
         *
         * Emit a message if too few or too many arguments have been passed
         * by the caller.
         *
         * Note: Too many arguments will not cause the method to
         * fail. However, the method will fail if there are too few
         * arguments and the method attempts to use one of the missing ones.
         */
        AmlParamCount = Node->Object->Method.ParamCount;

        if (UserParamCount < AmlParamCount)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Insufficient arguments - "
                "Caller passed %u, method requires %u",
                UserParamCount, AmlParamCount));
        }
        else if (UserParamCount > AmlParamCount)
        {
            ACPI_INFO_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Excess arguments - "
                "Caller passed %u, method requires %u",
                UserParamCount, AmlParamCount));
        }

        return;
    }

    /*
     * This is a predefined name. Validate the user-supplied parameter
     * count against the ACPI specification. We don't validate against
     * the method itself because what is important here is that the
     * caller is in conformance with the spec. (The arg count for the
     * method was checked against the ACPI spec earlier.)
     *
     * Some methods are allowed to have a "minimum" number of args (_SCP)
     * because their definition in ACPI has changed over time.
     */
    RequiredParamCount =
        METHOD_GET_ARG_COUNT (Predefined->Info.ArgumentList);

    if (UserParamCount < RequiredParamCount)
    {
        ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
            "Insufficient arguments - "
            "Caller passed %u, ACPI requires %u",
            UserParamCount, RequiredParamCount));
    }
    else if ((UserParamCount > RequiredParamCount) &&
        !(Predefined->Info.ArgumentList & ARG_COUNT_IS_MINIMUM))
    {
        ACPI_INFO_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
            "Excess arguments - "
            "Caller passed %u, ACPI requires %u",
            UserParamCount, RequiredParamCount));
    }
}