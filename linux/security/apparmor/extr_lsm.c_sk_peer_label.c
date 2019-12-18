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
struct aa_sk_ctx {struct aa_label* peer; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOPROTOOPT ; 
 struct aa_label* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct aa_sk_ctx* SK_CTX (struct sock*) ; 

__attribute__((used)) static struct aa_label *sk_peer_label(struct sock *sk)
{
	struct aa_sk_ctx *ctx = SK_CTX(sk);

	if (ctx->peer)
		return ctx->peer;

	return ERR_PTR(-ENOPROTOOPT);
}