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
struct ubuf_info {int /*<<< orphan*/  len; } ;
struct sock {int /*<<< orphan*/  sk_zckey; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_from_uarg (struct ubuf_info*) ; 
 int /*<<< orphan*/  sock_zerocopy_put (struct ubuf_info*) ; 

void sock_zerocopy_put_abort(struct ubuf_info *uarg, bool have_uref)
{
	if (uarg) {
		struct sock *sk = skb_from_uarg(uarg)->sk;

		atomic_dec(&sk->sk_zckey);
		uarg->len--;

		if (have_uref)
			sock_zerocopy_put(uarg);
	}
}