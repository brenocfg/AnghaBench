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
struct sk_buff {scalar_t__ fclone; } ;

/* Variables and functions */
 scalar_t__ SKB_FCLONE_UNAVAILABLE ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  _kfree_skb_defer (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unref (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_consume_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void napi_consume_skb(struct sk_buff *skb, int budget)
{
	if (unlikely(!skb))
		return;

	/* Zero budget indicate non-NAPI context called us, like netpoll */
	if (unlikely(!budget)) {
		dev_consume_skb_any(skb);
		return;
	}

	if (!skb_unref(skb))
		return;

	/* if reaching here SKB is ready to free */
	trace_consume_skb(skb);

	/* if SKB is a clone, don't handle this case */
	if (skb->fclone != SKB_FCLONE_UNAVAILABLE) {
		__kfree_skb(skb);
		return;
	}

	_kfree_skb_defer(skb);
}