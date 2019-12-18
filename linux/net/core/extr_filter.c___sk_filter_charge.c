#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct sk_filter {TYPE_1__* prog; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bpf_prog_size (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_optmem_max ; 

__attribute__((used)) static bool __sk_filter_charge(struct sock *sk, struct sk_filter *fp)
{
	u32 filter_size = bpf_prog_size(fp->prog->len);

	/* same check as in sock_kmalloc() */
	if (filter_size <= sysctl_optmem_max &&
	    atomic_read(&sk->sk_omem_alloc) + filter_size < sysctl_optmem_max) {
		atomic_add(filter_size, &sk->sk_omem_alloc);
		return true;
	}
	return false;
}