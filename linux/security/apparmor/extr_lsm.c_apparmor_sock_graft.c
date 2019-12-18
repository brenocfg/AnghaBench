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
struct socket {int dummy; } ;
struct sock {int dummy; } ;
struct aa_sk_ctx {scalar_t__ label; } ;

/* Variables and functions */
 struct aa_sk_ctx* SK_CTX (struct sock*) ; 
 scalar_t__ aa_get_current_label () ; 

__attribute__((used)) static void apparmor_sock_graft(struct sock *sk, struct socket *parent)
{
	struct aa_sk_ctx *ctx = SK_CTX(sk);

	if (!ctx->label)
		ctx->label = aa_get_current_label();
}