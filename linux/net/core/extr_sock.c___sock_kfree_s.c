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
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kzfree (void*) ; 

__attribute__((used)) static inline void __sock_kfree_s(struct sock *sk, void *mem, int size,
				  const bool nullify)
{
	if (WARN_ON_ONCE(!mem))
		return;
	if (nullify)
		kzfree(mem);
	else
		kfree(mem);
	atomic_sub(size, &sk->sk_omem_alloc);
}