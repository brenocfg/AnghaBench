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
struct ubuf_info {int /*<<< orphan*/  zerocopy; int /*<<< orphan*/  (* callback ) (struct ubuf_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_from_uarg (struct ubuf_info*) ; 
 int /*<<< orphan*/  stub1 (struct ubuf_info*,int /*<<< orphan*/ ) ; 

void sock_zerocopy_put(struct ubuf_info *uarg)
{
	if (uarg && refcount_dec_and_test(&uarg->refcnt)) {
		if (uarg->callback)
			uarg->callback(uarg, uarg->zerocopy);
		else
			consume_skb(skb_from_uarg(uarg));
	}
}