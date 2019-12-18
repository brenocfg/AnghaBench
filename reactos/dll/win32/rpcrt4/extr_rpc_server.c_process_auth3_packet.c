#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {scalar_t__ BufferLength; } ;
struct TYPE_7__ {int /*<<< orphan*/  SyntaxGUID; } ;
struct TYPE_8__ {TYPE_1__ ActiveInterface; } ;
typedef  int /*<<< orphan*/  RpcPktCommonHdr ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RpcAuthVerifier ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  TYPE_3__ RPC_MESSAGE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPCRT4_ServerConnectionAuth (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_PROTOCOL_ERROR ; 
 scalar_t__ UuidIsNil (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RPC_STATUS process_auth3_packet(RpcConnection *conn,
                                       RpcPktCommonHdr *hdr,
                                       RPC_MESSAGE *msg,
                                       unsigned char *auth_data,
                                       ULONG auth_length)
{
    RPC_STATUS status;

    if (UuidIsNil(&conn->ActiveInterface.SyntaxGUID, &status) ||
        !auth_length || msg->BufferLength != 0)
        status = RPC_S_PROTOCOL_ERROR;
    else
    {
        status = RPCRT4_ServerConnectionAuth(conn, FALSE,
                                             (RpcAuthVerifier *)auth_data,
                                             auth_length, NULL, NULL);
    }

    /* FIXME: client doesn't expect a response to this message so must store
     * status in connection so that fault packet can be returned when next
     * packet is received */

    return RPC_S_OK;
}