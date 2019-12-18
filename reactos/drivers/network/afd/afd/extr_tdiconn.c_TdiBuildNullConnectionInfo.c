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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  TDI_CONNECTION_INFORMATION ;
typedef  int /*<<< orphan*/ * PTDI_CONNECTION_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TAG_AFD_TDI_CONNECTION_INFORMATION ; 
 scalar_t__ TaLengthOfTransportAddressByType (scalar_t__) ; 
 int /*<<< orphan*/  TdiBuildNullConnectionInfoInPlace (int /*<<< orphan*/ *,scalar_t__) ; 

NTSTATUS TdiBuildNullConnectionInfo
( PTDI_CONNECTION_INFORMATION *ConnectionInfo,
  ULONG Type )
/*
 * FUNCTION: Builds a NULL TDI connection information structure
 * ARGUMENTS:
 *     ConnectionInfo = Address of buffer pointer to allocate connection
 *                      information in
 *     Type           = TDI style address type (TDI_ADDRESS_TYPE_XXX).
 * RETURNS:
 *     Status of operation
 */
{
    PTDI_CONNECTION_INFORMATION ConnInfo;
    ULONG TdiAddressSize;
    NTSTATUS Status;

    TdiAddressSize = TaLengthOfTransportAddressByType(Type);
    if (!TdiAddressSize) {
        AFD_DbgPrint(MIN_TRACE,("Invalid parameter\n"));
        *ConnectionInfo = NULL;
        return STATUS_INVALID_PARAMETER;
    }

    ConnInfo = (PTDI_CONNECTION_INFORMATION)
        ExAllocatePoolWithTag(NonPagedPool,
                              sizeof(TDI_CONNECTION_INFORMATION) + TdiAddressSize,
                              TAG_AFD_TDI_CONNECTION_INFORMATION);
    if (!ConnInfo) {
        *ConnectionInfo = NULL;
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = TdiBuildNullConnectionInfoInPlace( ConnInfo, Type );

    if (!NT_SUCCESS(Status))
    {
        ExFreePoolWithTag(ConnInfo, TAG_AFD_TDI_CONNECTION_INFORMATION);
        ConnInfo = NULL;
    }

    *ConnectionInfo = ConnInfo;

    return Status;
}