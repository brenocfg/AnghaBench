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
struct sock {int dummy; } ;
struct sctp_sock {int /*<<< orphan*/  hmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_sock_destruct (struct sock*) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 

__attribute__((used)) static void sctp_destruct_sock(struct sock *sk)
{
	struct sctp_sock *sp = sctp_sk(sk);

	/* Free up the HMAC transform. */
	crypto_free_shash(sp->hmac);

	inet_sock_destruct(sk);
}