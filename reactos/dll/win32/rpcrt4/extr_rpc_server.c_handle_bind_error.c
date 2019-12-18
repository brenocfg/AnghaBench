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
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int RPC_STATUS ;

/* Variables and functions */
#define  ERROR_ACCESS_DENIED 134 
#define  ERROR_OUTOFMEMORY 133 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  NDR_LOCAL_DATA_REPRESENTATION ; 
 unsigned int REJECT_INVALID_CHECKSUM ; 
 unsigned int REJECT_LOCAL_LIMIT_EXCEEDED ; 
 unsigned int REJECT_PROTOCOL_VERSION_NOT_SUPPORTED ; 
 unsigned int REJECT_REASON_NOT_SPECIFIED ; 
 unsigned int REJECT_TEMPORARY_CONGESTION ; 
 unsigned int REJECT_UNKNOWN_AUTHN_SERVICE ; 
 int /*<<< orphan*/ * RPCRT4_BuildBindNackHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
#define  RPC_S_INVALID_BOUND 132 
#define  RPC_S_OUT_OF_RESOURCES 131 
#define  RPC_S_PROTOCOL_ERROR 130 
#define  RPC_S_SERVER_TOO_BUSY 129 
#define  RPC_S_UNKNOWN_AUTHN_SERVICE 128 
 int /*<<< orphan*/  RPC_VER_MAJOR ; 
 int /*<<< orphan*/  RPC_VER_MINOR ; 

__attribute__((used)) static RpcPktHdr *handle_bind_error(RpcConnection *conn, RPC_STATUS error)
{
    unsigned int reject_reason;
    switch (error)
    {
    case RPC_S_SERVER_TOO_BUSY:
        reject_reason = REJECT_TEMPORARY_CONGESTION;
        break;
    case ERROR_OUTOFMEMORY:
    case RPC_S_OUT_OF_RESOURCES:
        reject_reason = REJECT_LOCAL_LIMIT_EXCEEDED;
        break;
    case RPC_S_PROTOCOL_ERROR:
        reject_reason = REJECT_PROTOCOL_VERSION_NOT_SUPPORTED;
        break;
    case RPC_S_UNKNOWN_AUTHN_SERVICE:
        reject_reason = REJECT_UNKNOWN_AUTHN_SERVICE;
        break;
    case ERROR_ACCESS_DENIED:
        reject_reason = REJECT_INVALID_CHECKSUM;
        break;
    default:
        FIXME("unexpected status value %d\n", error);
        /* fall through */
    case RPC_S_INVALID_BOUND:
        reject_reason = REJECT_REASON_NOT_SPECIFIED;
        break;
    }
    return RPCRT4_BuildBindNackHeader(NDR_LOCAL_DATA_REPRESENTATION,
                                      RPC_VER_MAJOR, RPC_VER_MINOR,
                                      reject_reason);
}