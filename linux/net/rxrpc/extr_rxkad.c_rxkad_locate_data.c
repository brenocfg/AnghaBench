#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rxrpc_call {TYPE_2__* conn; } ;
struct TYPE_3__ {int security_level; } ;
struct TYPE_4__ {TYPE_1__ params; } ;

/* Variables and functions */
#define  RXRPC_SECURITY_AUTH 129 
#define  RXRPC_SECURITY_ENCRYPT 128 
 int /*<<< orphan*/  rxkad_locate_data_1 (struct rxrpc_call*,struct sk_buff*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  rxkad_locate_data_2 (struct rxrpc_call*,struct sk_buff*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void rxkad_locate_data(struct rxrpc_call *call, struct sk_buff *skb,
			      unsigned int *_offset, unsigned int *_len)
{
	switch (call->conn->params.security_level) {
	case RXRPC_SECURITY_AUTH:
		rxkad_locate_data_1(call, skb, _offset, _len);
		return;
	case RXRPC_SECURITY_ENCRYPT:
		rxkad_locate_data_2(call, skb, _offset, _len);
		return;
	default:
		return;
	}
}