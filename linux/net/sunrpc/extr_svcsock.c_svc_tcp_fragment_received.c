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
struct svc_sock {scalar_t__ sk_reclen; scalar_t__ sk_tcplen; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ svc_sock_final_rec (struct svc_sock*) ; 
 int /*<<< orphan*/  svc_sock_reclen (struct svc_sock*) ; 

__attribute__((used)) static void svc_tcp_fragment_received(struct svc_sock *svsk)
{
	/* If we have more data, signal svc_xprt_enqueue() to try again */
	dprintk("svc: TCP %s record (%d bytes)\n",
		svc_sock_final_rec(svsk) ? "final" : "nonfinal",
		svc_sock_reclen(svsk));
	svsk->sk_tcplen = 0;
	svsk->sk_reclen = 0;
}