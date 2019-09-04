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
typedef  int u8 ;
struct pda_channel_output_limit {int dummy; } ;
struct p54_common {TYPE_1__* output_limit; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct p54_common* priv; } ;
struct TYPE_2__ {int entries; int entry_size; int /*<<< orphan*/  data; scalar_t__ offset; scalar_t__ len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int p54_convert_output_limits(struct ieee80211_hw *dev,
				     u8 *data, size_t len)
{
	struct p54_common *priv = dev->priv;

	if (len < 2)
		return -EINVAL;

	if (data[0] != 0) {
		wiphy_err(dev->wiphy, "unknown output power db revision:%x\n",
			  data[0]);
		return -EINVAL;
	}

	if (2 + data[1] * sizeof(struct pda_channel_output_limit) > len)
		return -EINVAL;

	priv->output_limit = kmalloc(data[1] *
		sizeof(struct pda_channel_output_limit) +
		sizeof(*priv->output_limit), GFP_KERNEL);

	if (!priv->output_limit)
		return -ENOMEM;

	priv->output_limit->offset = 0;
	priv->output_limit->entries = data[1];
	priv->output_limit->entry_size =
		sizeof(struct pda_channel_output_limit);
	priv->output_limit->len = priv->output_limit->entry_size *
				  priv->output_limit->entries +
				  priv->output_limit->offset;

	memcpy(priv->output_limit->data, &data[2],
	       data[1] * sizeof(struct pda_channel_output_limit));

	return 0;
}