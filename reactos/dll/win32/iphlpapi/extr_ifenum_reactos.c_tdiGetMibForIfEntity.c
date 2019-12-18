#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
struct TYPE_12__ {int* if_physaddr; int /*<<< orphan*/  if_descr; int /*<<< orphan*/  if_descrlen; int /*<<< orphan*/  if_physaddrlen; int /*<<< orphan*/  if_speed; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_type; int /*<<< orphan*/  if_index; } ;
struct TYPE_15__ {TYPE_2__ ent; } ;
struct TYPE_13__ {int /*<<< orphan*/  tei_instance; } ;
struct TYPE_11__ {TYPE_3__ toi_entity; int /*<<< orphan*/  toi_id; int /*<<< orphan*/  toi_type; int /*<<< orphan*/  toi_class; } ;
struct TYPE_14__ {TYPE_1__ ID; } ;
typedef  TYPE_3__ TDIEntityID ;
typedef  TYPE_4__ TCP_REQUEST_QUERY_INFORMATION_EX ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_5__ IFEntrySafelySized ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_MIB_STATS_ID ; 
 int /*<<< orphan*/  INFO_CLASS_PROTOCOL ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  IOCTL_TCP_QUERY_INFORMATION_EX ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 TYPE_4__ TCP_REQUEST_QUERY_INFORMATION_INIT ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 

NTSTATUS tdiGetMibForIfEntity
( HANDLE tcpFile, TDIEntityID *ent, IFEntrySafelySized *entry ) {
    TCP_REQUEST_QUERY_INFORMATION_EX req = TCP_REQUEST_QUERY_INFORMATION_INIT;
    NTSTATUS status = STATUS_SUCCESS;
    DWORD returnSize;

    WARN("TdiGetMibForIfEntity(tcpFile %p,entityId %p)\n",
           tcpFile, ent->tei_instance);

    req.ID.toi_class                = INFO_CLASS_PROTOCOL;
    req.ID.toi_type                 = INFO_TYPE_PROVIDER;
    req.ID.toi_id                   = IF_MIB_STATS_ID;
    req.ID.toi_entity               = *ent;

    status = DeviceIoControl( tcpFile,
                              IOCTL_TCP_QUERY_INFORMATION_EX,
                              &req,
                              sizeof(req),
                              entry,
                              sizeof(*entry),
                              &returnSize,
                              NULL );

    if(!status)
    {
            WARN("IOCTL Failed\n");
            return STATUS_UNSUCCESSFUL;
    }

    TRACE("TdiGetMibForIfEntity() => {\n"
           "  if_index ....................... %x\n"
           "  if_type ........................ %x\n"
           "  if_mtu ......................... %d\n"
           "  if_speed ....................... %x\n"
           "  if_physaddrlen ................. %d\n",
           entry->ent.if_index,
           entry->ent.if_type,
           entry->ent.if_mtu,
           entry->ent.if_speed,
           entry->ent.if_physaddrlen);
    TRACE("  if_physaddr .................... %02x:%02x:%02x:%02x:%02x:%02x\n"
           "  if_descr ....................... %*s\n",
           entry->ent.if_physaddr[0] & 0xff,
           entry->ent.if_physaddr[1] & 0xff,
           entry->ent.if_physaddr[2] & 0xff,
           entry->ent.if_physaddr[3] & 0xff,
           entry->ent.if_physaddr[4] & 0xff,
           entry->ent.if_physaddr[5] & 0xff,
           entry->ent.if_descrlen,
           entry->ent.if_descr);
    TRACE("} status %08x\n",status);

    return STATUS_SUCCESS;
}