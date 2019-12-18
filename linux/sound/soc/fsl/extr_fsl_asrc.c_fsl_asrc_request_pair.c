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
struct fsl_asrc_pair {int channels; int index; struct fsl_asrc* asrc_priv; } ;
struct fsl_asrc {int channel_avail; int /*<<< orphan*/  lock; struct fsl_asrc_pair** pair; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  enum asrc_pair_index { ____Placeholder_asrc_pair_index } asrc_pair_index ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ASRC_INVALID_PAIR ; 
 int ASRC_PAIR_A ; 
 int ASRC_PAIR_B ; 
 int ASRC_PAIR_MAX_NUM ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fsl_asrc_request_pair(int channels, struct fsl_asrc_pair *pair)
{
	enum asrc_pair_index index = ASRC_INVALID_PAIR;
	struct fsl_asrc *asrc_priv = pair->asrc_priv;
	struct device *dev = &asrc_priv->pdev->dev;
	unsigned long lock_flags;
	int i, ret = 0;

	spin_lock_irqsave(&asrc_priv->lock, lock_flags);

	for (i = ASRC_PAIR_A; i < ASRC_PAIR_MAX_NUM; i++) {
		if (asrc_priv->pair[i] != NULL)
			continue;

		index = i;

		if (i != ASRC_PAIR_B)
			break;
	}

	if (index == ASRC_INVALID_PAIR) {
		dev_err(dev, "all pairs are busy now\n");
		ret = -EBUSY;
	} else if (asrc_priv->channel_avail < channels) {
		dev_err(dev, "can't afford required channels: %d\n", channels);
		ret = -EINVAL;
	} else {
		asrc_priv->channel_avail -= channels;
		asrc_priv->pair[index] = pair;
		pair->channels = channels;
		pair->index = index;
	}

	spin_unlock_irqrestore(&asrc_priv->lock, lock_flags);

	return ret;
}