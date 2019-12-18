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
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiNsBuildNormalizedPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 

ACPI_SIZE
AcpiNsGetPathnameLength (
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_SIZE               Size;


    /* Validate the Node */

    if (ACPI_GET_DESCRIPTOR_TYPE (Node) != ACPI_DESC_TYPE_NAMED)
    {
        ACPI_ERROR ((AE_INFO,
            "Invalid/cached reference target node: %p, descriptor type %d",
            Node, ACPI_GET_DESCRIPTOR_TYPE (Node)));
        return (0);
    }

    Size = AcpiNsBuildNormalizedPath (Node, NULL, 0, FALSE);
    return (Size);
}