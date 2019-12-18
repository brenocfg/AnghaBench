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
typedef  void* UINT ;
struct TYPE_9__ {void* InformationBufferLength; void* InformationBuffer; void* Oid; } ;
struct TYPE_8__ {void* InformationBufferLength; void* InformationBuffer; void* Oid; } ;
struct TYPE_10__ {TYPE_2__ QUERY_INFORMATION; TYPE_1__ SET_INFORMATION; } ;
struct TYPE_12__ {TYPE_3__ DATA; scalar_t__ RequestType; } ;
struct TYPE_11__ {scalar_t__ State; scalar_t__ NdisStatus; int /*<<< orphan*/  Event; int /*<<< orphan*/  NdisHandle; } ;
typedef  void* PVOID ;
typedef  TYPE_4__* PLAN_ADAPTER ;
typedef  scalar_t__ NDIS_STATUS ;
typedef  scalar_t__ NDIS_REQUEST_TYPE ;
typedef  TYPE_5__ NDIS_REQUEST ;
typedef  void* NDIS_OID ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 scalar_t__ LAN_STATE_RESETTING ; 
 scalar_t__ NDIS_STATUS_NOT_ACCEPTED ; 
 scalar_t__ NDIS_STATUS_PENDING ; 
 int /*<<< orphan*/  NdisRequest (scalar_t__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ NdisRequestSetInformation ; 
 int /*<<< orphan*/  UserRequest ; 

NDIS_STATUS NDISCall(
    PLAN_ADAPTER Adapter,
    NDIS_REQUEST_TYPE Type,
    NDIS_OID OID,
    PVOID Buffer,
    UINT Length)
/*
 * FUNCTION: Send a request to NDIS
 * ARGUMENTS:
 *     Adapter     = Pointer to a LAN_ADAPTER structure
 *     Type        = Type of request (Set or Query)
 *     OID         = Value to be set/queried for
 *     Buffer      = Pointer to a buffer to use
 *     Length      = Number of bytes in Buffer
 * RETURNS:
 *     Status of operation
 */
{
    NDIS_REQUEST Request;
    NDIS_STATUS NdisStatus;

    Request.RequestType = Type;
    if (Type == NdisRequestSetInformation) {
        Request.DATA.SET_INFORMATION.Oid                     = OID;
        Request.DATA.SET_INFORMATION.InformationBuffer       = Buffer;
        Request.DATA.SET_INFORMATION.InformationBufferLength = Length;
    } else {
        Request.DATA.QUERY_INFORMATION.Oid                     = OID;
        Request.DATA.QUERY_INFORMATION.InformationBuffer       = Buffer;
        Request.DATA.QUERY_INFORMATION.InformationBufferLength = Length;
    }

    if (Adapter->State != LAN_STATE_RESETTING) {
        NdisRequest(&NdisStatus, Adapter->NdisHandle, &Request);
    } else {
        NdisStatus = NDIS_STATUS_NOT_ACCEPTED;
    }

    /* Wait for NDIS to complete the request */
    if (NdisStatus == NDIS_STATUS_PENDING) {
        KeWaitForSingleObject(&Adapter->Event,
                              UserRequest,
                              KernelMode,
                              FALSE,
                              NULL);
        NdisStatus = Adapter->NdisStatus;
    }

    return NdisStatus;
}