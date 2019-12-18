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
typedef  int /*<<< orphan*/  u32 ;
struct rxrpc_call {int completion; int /*<<< orphan*/  rx_pkt_len; int /*<<< orphan*/  rx_pkt_offset; int /*<<< orphan*/  rx_hard_ack; int /*<<< orphan*/  state; int /*<<< orphan*/  error; int /*<<< orphan*/  abort_code; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  RXRPC_ABORT ; 
 int /*<<< orphan*/  RXRPC_ACK ; 
#define  RXRPC_CALL_LOCALLY_ABORTED 132 
#define  RXRPC_CALL_LOCAL_ERROR 131 
#define  RXRPC_CALL_NETWORK_ERROR 130 
#define  RXRPC_CALL_REMOTELY_ABORTED 129 
#define  RXRPC_CALL_SUCCEEDED 128 
 int /*<<< orphan*/  RXRPC_LOCAL_ERROR ; 
 int /*<<< orphan*/  RXRPC_NET_ERROR ; 
 int /*<<< orphan*/  SOL_RXRPC ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_is_service_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_recvmsg_terminal ; 
 int /*<<< orphan*/  trace_rxrpc_recvmsg (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rxrpc_recvmsg_term(struct rxrpc_call *call, struct msghdr *msg)
{
	u32 tmp = 0;
	int ret;

	switch (call->completion) {
	case RXRPC_CALL_SUCCEEDED:
		ret = 0;
		if (rxrpc_is_service_call(call))
			ret = put_cmsg(msg, SOL_RXRPC, RXRPC_ACK, 0, &tmp);
		break;
	case RXRPC_CALL_REMOTELY_ABORTED:
		tmp = call->abort_code;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_ABORT, 4, &tmp);
		break;
	case RXRPC_CALL_LOCALLY_ABORTED:
		tmp = call->abort_code;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_ABORT, 4, &tmp);
		break;
	case RXRPC_CALL_NETWORK_ERROR:
		tmp = -call->error;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_NET_ERROR, 4, &tmp);
		break;
	case RXRPC_CALL_LOCAL_ERROR:
		tmp = -call->error;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_LOCAL_ERROR, 4, &tmp);
		break;
	default:
		pr_err("Invalid terminal call state %u\n", call->state);
		BUG();
		break;
	}

	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_terminal, call->rx_hard_ack,
			    call->rx_pkt_offset, call->rx_pkt_len, ret);
	return ret;
}