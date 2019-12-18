#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int OptionsLength; scalar_t__ RemoteAddress; scalar_t__ RemoteAddressLength; } ;
typedef  int /*<<< orphan*/  TDI_CONNECTION_INFORMATION ;
typedef  scalar_t__ PTRANSPORT_ADDRESS ;
typedef  TYPE_1__* PTDI_CONNECTION_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 scalar_t__ TaLengthOfTransportAddressByType (scalar_t__) ; 
 int /*<<< orphan*/  TdiBuildNullTransportAddressInPlace (scalar_t__,scalar_t__) ; 

NTSTATUS TdiBuildNullConnectionInfoInPlace
( PTDI_CONNECTION_INFORMATION ConnInfo,
  ULONG Type )
/*
 * FUNCTION: Builds a NULL TDI connection information structure
 * ARGUMENTS:
 *     ConnectionInfo = Address of buffer to place connection information
 *     Type           = TDI style address type (TDI_ADDRESS_TYPE_XXX).
 * RETURNS:
 *     Status of operation
 */
{
    ULONG TdiAddressSize;
    PTRANSPORT_ADDRESS TransportAddress;

    TdiAddressSize = TaLengthOfTransportAddressByType(Type);
    if (!TdiAddressSize)
    {
        AFD_DbgPrint(MIN_TRACE,("Invalid parameter\n"));
        return STATUS_INVALID_PARAMETER;
    }

    RtlZeroMemory(ConnInfo,
                  sizeof(TDI_CONNECTION_INFORMATION) +
                  TdiAddressSize);

    ConnInfo->OptionsLength = sizeof(ULONG);
    ConnInfo->RemoteAddressLength = TdiAddressSize;
    ConnInfo->RemoteAddress = TransportAddress =
        (PTRANSPORT_ADDRESS)&ConnInfo[1];

    return TdiBuildNullTransportAddressInPlace(TransportAddress, Type);
}