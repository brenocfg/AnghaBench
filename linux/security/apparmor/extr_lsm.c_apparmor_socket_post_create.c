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
struct socket {scalar_t__ sk; } ;
struct aa_sk_ctx {struct aa_label* label; } ;
struct aa_ns {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_sk_ctx* SK_CTX (scalar_t__) ; 
 struct aa_label* aa_get_current_label () ; 
 struct aa_ns* aa_get_current_ns () ; 
 void* aa_get_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 struct aa_label* ns_unconfined (struct aa_ns*) ; 

__attribute__((used)) static int apparmor_socket_post_create(struct socket *sock, int family,
				       int type, int protocol, int kern)
{
	struct aa_label *label;

	if (kern) {
		struct aa_ns *ns = aa_get_current_ns();

		label = aa_get_label(ns_unconfined(ns));
		aa_put_ns(ns);
	} else
		label = aa_get_current_label();

	if (sock->sk) {
		struct aa_sk_ctx *ctx = SK_CTX(sock->sk);

		aa_put_label(ctx->label);
		ctx->label = aa_get_label(label);
	}
	aa_put_label(label);

	return 0;
}