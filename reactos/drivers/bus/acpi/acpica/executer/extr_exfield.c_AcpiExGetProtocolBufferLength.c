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
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_INVALID_PROTOCOL_ID ; 
 size_t ACPI_MAX_PROTOCOL_ID ; 
 int /*<<< orphan*/  AE_AML_PROTOCOL ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__* AcpiProtocolLengths ; 

ACPI_STATUS
AcpiExGetProtocolBufferLength (
    UINT32                  ProtocolId,
    UINT32                  *ReturnLength)
{

    if ((ProtocolId > ACPI_MAX_PROTOCOL_ID) ||
        (AcpiProtocolLengths[ProtocolId] == ACPI_INVALID_PROTOCOL_ID))
    {
        ACPI_ERROR ((AE_INFO,
            "Invalid Field/AccessAs protocol ID: 0x%4.4X", ProtocolId));

        return (AE_AML_PROTOCOL);
    }

    *ReturnLength = AcpiProtocolLengths[ProtocolId];
    return (AE_OK);
}