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
struct sk_buff {struct sec_path* sp; } ;
struct sec_path {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 struct sec_path* secpath_dup (struct sec_path*) ; 
 int /*<<< orphan*/  secpath_put (struct sec_path*) ; 

int secpath_set(struct sk_buff *skb)
{
	struct sec_path *sp;

	/* Allocate new secpath or COW existing one. */
	if (!skb->sp || refcount_read(&skb->sp->refcnt) != 1) {
		sp = secpath_dup(skb->sp);
		if (!sp)
			return -ENOMEM;

		if (skb->sp)
			secpath_put(skb->sp);
		skb->sp = sp;
	}
	return 0;
}