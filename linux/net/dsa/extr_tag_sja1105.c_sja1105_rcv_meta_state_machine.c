#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ dev; } ;
struct sja1105_port {TYPE_2__* data; } ;
struct sja1105_meta {int dummy; } ;
struct dsa_port {TYPE_1__* ds; struct sja1105_port* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  meta_lock; struct sk_buff* stampable_skb; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1105_HWTS_RX_EN ; 
 int /*<<< orphan*/  SJA1105_META_DMAC ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 struct dsa_port* dsa_slave_to_port (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sja1105_transfer_meta (struct sk_buff*,struct sja1105_meta*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff
*sja1105_rcv_meta_state_machine(struct sk_buff *skb,
				struct sja1105_meta *meta,
				bool is_link_local,
				bool is_meta)
{
	struct sja1105_port *sp;
	struct dsa_port *dp;

	dp = dsa_slave_to_port(skb->dev);
	sp = dp->priv;

	/* Step 1: A timestampable frame was received.
	 * Buffer it until we get its meta frame.
	 */
	if (is_link_local) {
		if (!test_bit(SJA1105_HWTS_RX_EN, &sp->data->state))
			/* Do normal processing. */
			return skb;

		spin_lock(&sp->data->meta_lock);
		/* Was this a link-local frame instead of the meta
		 * that we were expecting?
		 */
		if (sp->data->stampable_skb) {
			dev_err_ratelimited(dp->ds->dev,
					    "Expected meta frame, is %12llx "
					    "in the DSA master multicast filter?\n",
					    SJA1105_META_DMAC);
			kfree_skb(sp->data->stampable_skb);
		}

		/* Hold a reference to avoid dsa_switch_rcv
		 * from freeing the skb.
		 */
		sp->data->stampable_skb = skb_get(skb);
		spin_unlock(&sp->data->meta_lock);

		/* Tell DSA we got nothing */
		return NULL;

	/* Step 2: The meta frame arrived.
	 * Time to take the stampable skb out of the closet, annotate it
	 * with the partial timestamp, and pretend that we received it
	 * just now (basically masquerade the buffered frame as the meta
	 * frame, which serves no further purpose).
	 */
	} else if (is_meta) {
		struct sk_buff *stampable_skb;

		/* Drop the meta frame if we're not in the right state
		 * to process it.
		 */
		if (!test_bit(SJA1105_HWTS_RX_EN, &sp->data->state))
			return NULL;

		spin_lock(&sp->data->meta_lock);

		stampable_skb = sp->data->stampable_skb;
		sp->data->stampable_skb = NULL;

		/* Was this a meta frame instead of the link-local
		 * that we were expecting?
		 */
		if (!stampable_skb) {
			dev_err_ratelimited(dp->ds->dev,
					    "Unexpected meta frame\n");
			spin_unlock(&sp->data->meta_lock);
			return NULL;
		}

		if (stampable_skb->dev != skb->dev) {
			dev_err_ratelimited(dp->ds->dev,
					    "Meta frame on wrong port\n");
			spin_unlock(&sp->data->meta_lock);
			return NULL;
		}

		/* Free the meta frame and give DSA the buffered stampable_skb
		 * for further processing up the network stack.
		 */
		kfree_skb(skb);
		skb = stampable_skb;
		sja1105_transfer_meta(skb, meta);

		spin_unlock(&sp->data->meta_lock);
	}

	return skb;
}