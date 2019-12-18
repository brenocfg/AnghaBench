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
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {scalar_t__ Count; TYPE_2__** Elements; } ;
struct TYPE_6__ {TYPE_1__ Package; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_2__*) ; 
 int /*<<< orphan*/  NsRemoveElement ; 

__attribute__((used)) static void
AcpiNsRemoveElement (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  Index)
{
    ACPI_OPERAND_OBJECT     **Source;
    ACPI_OPERAND_OBJECT     **Dest;
    UINT32                  Count;
    UINT32                  NewCount;
    UINT32                  i;


    ACPI_FUNCTION_NAME (NsRemoveElement);


    Count = ObjDesc->Package.Count;
    NewCount = Count - 1;

    Source = ObjDesc->Package.Elements;
    Dest = Source;

    /* Examine all elements of the package object, remove matched index */

    for (i = 0; i < Count; i++)
    {
        if (i == Index)
        {
            AcpiUtRemoveReference (*Source); /* Remove one ref for being in pkg */
            AcpiUtRemoveReference (*Source);
        }
        else
        {
            *Dest = *Source;
            Dest++;
        }

        Source++;
    }

    /* NULL terminate list and update the package count */

    *Dest = NULL;
    ObjDesc->Package.Count = NewCount;
}