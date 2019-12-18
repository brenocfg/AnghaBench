#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tei_instance; } ;
typedef  TYPE_1__ TDIEntityID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PDWORD ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IPAddrEntry ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CL_NL_ENTITY ; 
 int /*<<< orphan*/  INFO_CLASS_PROTOCOL ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  IP_MIB_ADDRTABLE_ENTRY_ID ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiGetSetOfThings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS tdiGetIpAddrsForIpEntity
( HANDLE tcpFile, TDIEntityID *ent, IPAddrEntry **addrs, PDWORD numAddrs ) {
    NTSTATUS status;

    TRACE("TdiGetIpAddrsForIpEntity(tcpFile 0x%p, entityId 0x%x)\n",
          tcpFile, ent->tei_instance);

    status = tdiGetSetOfThings( tcpFile,
                                INFO_CLASS_PROTOCOL,
                                INFO_TYPE_PROVIDER,
                                IP_MIB_ADDRTABLE_ENTRY_ID,
                                CL_NL_ENTITY,
				ent->tei_instance,
                                0,
                                sizeof(IPAddrEntry),
                                (PVOID *)addrs,
                                numAddrs );

    return status;
}