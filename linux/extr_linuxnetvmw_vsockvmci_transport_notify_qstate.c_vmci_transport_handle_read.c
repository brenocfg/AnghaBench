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
struct vmci_transport_packet {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void
vmci_transport_handle_read(struct sock *sk,
			   struct vmci_transport_packet *pkt,
			   bool bottom_half,
			   struct sockaddr_vm *dst, struct sockaddr_vm *src)
{
	sk->sk_write_space(sk);
}