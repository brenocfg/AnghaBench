#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct protocol {int dummy; } ;
struct TYPE_19__ {TYPE_1__* client; } ;
struct TYPE_18__ {scalar_t__ dwIndex; } ;
struct TYPE_17__ {TYPE_7__ DhclientInfo; } ;
struct TYPE_14__ {int /*<<< orphan*/  String; } ;
struct TYPE_15__ {TYPE_2__ IpAddress; } ;
struct TYPE_16__ {scalar_t__ Index; TYPE_3__ IpAddressList; struct TYPE_16__* Next; } ;
struct TYPE_13__ {scalar_t__ state; } ;
typedef  TYPE_4__* PIP_ADAPTER_INFO ;
typedef  TYPE_5__* PDHCP_ADAPTER ;
typedef  TYPE_6__ MIB_IFROW ;
typedef  int /*<<< orphan*/  IP_ADAPTER_INFO ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ApiLock () ; 
 int /*<<< orphan*/  ApiUnlock () ; 
 scalar_t__ ERROR_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetAdaptersInfo (TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ NO_ERROR ; 
 scalar_t__ S_BOUND ; 
 scalar_t__ S_STATIC ; 
 int /*<<< orphan*/  TRUE ; 
 struct protocol* find_protocol_by_adapter (TYPE_7__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

BOOL
IsReconnectHackNeeded(PDHCP_ADAPTER Adapter, const MIB_IFROW* IfEntry)
{
    struct protocol *proto;
    PIP_ADAPTER_INFO AdapterInfo, Orig;
    DWORD Size, Ret;
    char *ZeroAddress = "0.0.0.0";

    proto = find_protocol_by_adapter(&Adapter->DhclientInfo);

    if (Adapter->DhclientInfo.client->state == S_BOUND && !proto)
        return FALSE;

    if (Adapter->DhclientInfo.client->state != S_BOUND &&
        Adapter->DhclientInfo.client->state != S_STATIC)
        return FALSE;
    
    ApiUnlock();

    Orig = AdapterInfo = HeapAlloc(GetProcessHeap(), 0, sizeof(IP_ADAPTER_INFO));
    Size = sizeof(IP_ADAPTER_INFO);
    if (!AdapterInfo)
    {
        ApiLock();
        return FALSE;
    }

    Ret = GetAdaptersInfo(AdapterInfo, &Size);
    if (Ret == ERROR_BUFFER_OVERFLOW)
    {
        HeapFree(GetProcessHeap(), 0, AdapterInfo);
        AdapterInfo = HeapAlloc(GetProcessHeap(), 0, Size);
        if (!AdapterInfo)
        {
            ApiLock();
            return FALSE;
        }

        if (GetAdaptersInfo(AdapterInfo, &Size) != NO_ERROR)
        {
            ApiLock();
            return FALSE;
        }

        Orig = AdapterInfo;
        for (; AdapterInfo != NULL; AdapterInfo = AdapterInfo->Next)
        {
            if (AdapterInfo->Index == IfEntry->dwIndex)
                break;
        }

        if (AdapterInfo == NULL)
        {
            HeapFree(GetProcessHeap(), 0, Orig);
            ApiLock();
            return FALSE;
        }
    }
    else if (Ret != NO_ERROR)
    {
        HeapFree(GetProcessHeap(), 0, Orig);
        ApiLock();
        return FALSE;
    }

    if (!strcmp(AdapterInfo->IpAddressList.IpAddress.String, ZeroAddress))
    {
        HeapFree(GetProcessHeap(), 0, Orig);
        ApiLock();
        return TRUE;
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, Orig);
        ApiLock();
        return FALSE;
    }
}