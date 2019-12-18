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
typedef  struct sock const sock ;
struct aa_sk_ctx {void* peer; void* label; } ;

/* Variables and functions */
 struct aa_sk_ctx* SK_CTX (struct sock const*) ; 
 void* aa_get_label (void*) ; 

__attribute__((used)) static void apparmor_sk_clone_security(const struct sock *sk,
				       struct sock *newsk)
{
	struct aa_sk_ctx *ctx = SK_CTX(sk);
	struct aa_sk_ctx *new = SK_CTX(newsk);

	new->label = aa_get_label(ctx->label);
	new->peer = aa_get_label(ctx->peer);
}