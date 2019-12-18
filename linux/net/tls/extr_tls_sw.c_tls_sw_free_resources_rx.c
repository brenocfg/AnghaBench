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
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int /*<<< orphan*/  tls_sw_free_ctx_rx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_sw_release_resources_rx (struct sock*) ; 

void tls_sw_free_resources_rx(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);

	tls_sw_release_resources_rx(sk);
	tls_sw_free_ctx_rx(tls_ctx);
}