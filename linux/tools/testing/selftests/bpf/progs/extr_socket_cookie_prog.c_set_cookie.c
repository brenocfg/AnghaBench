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
struct socket_cookie {int cookie_value; int /*<<< orphan*/  cookie_key; } ;
struct bpf_sock_addr {scalar_t__ family; scalar_t__ user_family; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  BPF_SK_STORAGE_GET_F_CREATE ; 
 int /*<<< orphan*/  bpf_get_socket_cookie (struct bpf_sock_addr*) ; 
 struct socket_cookie* bpf_sk_storage_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_cookies ; 

int set_cookie(struct bpf_sock_addr *ctx)
{
	struct socket_cookie *p;

	if (ctx->family != AF_INET6 || ctx->user_family != AF_INET6)
		return 1;

	p = bpf_sk_storage_get(&socket_cookies, ctx->sk, 0,
			       BPF_SK_STORAGE_GET_F_CREATE);
	if (!p)
		return 1;

	p->cookie_value = 0xFF;
	p->cookie_key = bpf_get_socket_cookie(ctx);

	return 1;
}