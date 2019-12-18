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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * PTRANSPORT_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_AFD_TRANSPORT_ADDRESS ; 
 int /*<<< orphan*/  TaLengthOfTransportAddressByType (int /*<<< orphan*/ ) ; 
 scalar_t__ TdiBuildNullTransportAddressInPlace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PTRANSPORT_ADDRESS TaBuildNullTransportAddress(UINT AddressType)
{
    UINT AddrLen;
    PTRANSPORT_ADDRESS A;

    AddrLen = TaLengthOfTransportAddressByType(AddressType);
    if (!AddrLen)
        return NULL;

    A = ExAllocatePoolWithTag(NonPagedPool, AddrLen, TAG_AFD_TRANSPORT_ADDRESS);

    if (A)
    {
        if (TdiBuildNullTransportAddressInPlace(A, AddressType) != STATUS_SUCCESS)
        {
            ExFreePoolWithTag(A, TAG_AFD_TRANSPORT_ADDRESS);
            return NULL;
        }
    }

    return A;
}