#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {unsigned char ptype; int call_id; scalar_t__ flags; scalar_t__ auth_len; void** drep; int /*<<< orphan*/  rpc_ver_minor; int /*<<< orphan*/  rpc_ver; } ;
struct TYPE_5__ {TYPE_1__ common; } ;
typedef  TYPE_2__ RpcPktHdr ;

/* Variables and functions */
 void* HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 void* LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_VER_MAJOR ; 
 int /*<<< orphan*/  RPC_VER_MINOR ; 

__attribute__((used)) static VOID RPCRT4_BuildCommonHeader(RpcPktHdr *Header, unsigned char PacketType,
                                     ULONG DataRepresentation)
{
  Header->common.rpc_ver = RPC_VER_MAJOR;
  Header->common.rpc_ver_minor = RPC_VER_MINOR;
  Header->common.ptype = PacketType;
  Header->common.drep[0] = LOBYTE(LOWORD(DataRepresentation));
  Header->common.drep[1] = HIBYTE(LOWORD(DataRepresentation));
  Header->common.drep[2] = LOBYTE(HIWORD(DataRepresentation));
  Header->common.drep[3] = HIBYTE(HIWORD(DataRepresentation));
  Header->common.auth_len = 0;
  Header->common.call_id = 1;
  Header->common.flags = 0;
  /* Flags and fragment length are computed in RPCRT4_Send. */
}