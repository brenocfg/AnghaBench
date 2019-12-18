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
typedef  enum secure_packet_direction { ____Placeholder_secure_packet_direction } secure_packet_direction ;
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int /*<<< orphan*/  RpcAuthVerifier ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_S_OK ; 

__attribute__((used)) static RPC_STATUS rpcrt4_ncalrpc_secure_packet(RpcConnection *conn,
    enum secure_packet_direction dir,
    RpcPktHdr *hdr, unsigned int hdr_size,
    unsigned char *stub_data, unsigned int stub_data_size,
    RpcAuthVerifier *auth_hdr,
    unsigned char *auth_value, unsigned int auth_value_size)
{
    /* since this protocol is local to the machine there is no need to secure
     * the packet */
    return RPC_S_OK;
}