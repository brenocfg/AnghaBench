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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct sk_filter {TYPE_1__* prog; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_filter_release (struct sk_filter*) ; 

void sk_filter_uncharge(struct sock *sk, struct sk_filter *fp)
{
	u32 filter_size = bpf_prog_size(fp->prog->len);

	atomic_sub(filter_size, &sk->sk_omem_alloc);
	sk_filter_release(fp);
}