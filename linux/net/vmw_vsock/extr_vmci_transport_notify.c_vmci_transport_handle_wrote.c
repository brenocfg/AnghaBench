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
struct vsock_sock {int dummy; } ;
struct vmci_transport_packet {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;

/* Variables and functions */
 int PKT_FIELD (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sent_waiting_read ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void
vmci_transport_handle_wrote(struct sock *sk,
			    struct vmci_transport_packet *pkt,
			    bool bottom_half,
			    struct sockaddr_vm *dst, struct sockaddr_vm *src)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	struct vsock_sock *vsk = vsock_sk(sk);
	PKT_FIELD(vsk, sent_waiting_read) = false;
#endif
	sk->sk_data_ready(sk);
}