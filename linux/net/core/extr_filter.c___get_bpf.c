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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
 int /*<<< orphan*/  EPERM ; 
 struct bpf_prog* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_FILTER_LOCKED ; 
 struct bpf_prog* bpf_prog_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_prog *__get_bpf(u32 ufd, struct sock *sk)
{
	if (sock_flag(sk, SOCK_FILTER_LOCKED))
		return ERR_PTR(-EPERM);

	return bpf_prog_get_type(ufd, BPF_PROG_TYPE_SOCKET_FILTER);
}