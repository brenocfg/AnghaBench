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
struct TYPE_3__ {scalar_t__ rpc_ver; scalar_t__ rpc_ver_minor; scalar_t__ frag_len; } ;
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  TYPE_1__ RpcPktCommonHdr ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ RPCRT4_GetHeaderSize (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_PROTOCOL_ERROR ; 
 scalar_t__ RPC_VER_MAJOR ; 
 scalar_t__ RPC_VER_MINOR ; 
 int /*<<< orphan*/  WARN (char*,...) ; 

RPC_STATUS RPCRT4_ValidateCommonHeader(const RpcPktCommonHdr *hdr)
{
  DWORD hdr_length;

  /* verify if the header really makes sense */
  if (hdr->rpc_ver != RPC_VER_MAJOR ||
      hdr->rpc_ver_minor != RPC_VER_MINOR)
  {
    WARN("unhandled packet version\n");
    return RPC_S_PROTOCOL_ERROR;
  }

  hdr_length = RPCRT4_GetHeaderSize((const RpcPktHdr*)hdr);
  if (hdr_length == 0)
  {
    WARN("header length == 0\n");
    return RPC_S_PROTOCOL_ERROR;
  }

  if (hdr->frag_len < hdr_length)
  {
    WARN("bad frag length %d\n", hdr->frag_len);
    return RPC_S_PROTOCOL_ERROR;
  }

  return RPC_S_OK;
}