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
struct sk_buff {int* data; } ;
struct nfc_llcp_sock {int send_n; int recv_n; int recv_ack_n; } ;

/* Variables and functions */

__attribute__((used)) static void nfc_llcp_set_nrns(struct nfc_llcp_sock *sock, struct sk_buff *pdu)
{
	pdu->data[2] = (sock->send_n << 4) | (sock->recv_n);
	sock->send_n = (sock->send_n + 1) % 16;
	sock->recv_ack_n = (sock->recv_n - 1) % 16;
}