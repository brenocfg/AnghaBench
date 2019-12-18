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
struct fsl_asrc_pair {int index; scalar_t__ error; scalar_t__ channels; struct fsl_asrc* asrc_priv; } ;
struct fsl_asrc {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** pair; int /*<<< orphan*/  channel_avail; int /*<<< orphan*/  regmap; } ;
typedef  enum asrc_pair_index { ____Placeholder_asrc_pair_index } asrc_pair_index ;

/* Variables and functions */
 int /*<<< orphan*/  ASRCTR_ASRCEi_MASK (int) ; 
 int /*<<< orphan*/  REG_ASRCTR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fsl_asrc_release_pair(struct fsl_asrc_pair *pair)
{
	struct fsl_asrc *asrc_priv = pair->asrc_priv;
	enum asrc_pair_index index = pair->index;
	unsigned long lock_flags;

	/* Make sure the pair is disabled */
	regmap_update_bits(asrc_priv->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_MASK(index), 0);

	spin_lock_irqsave(&asrc_priv->lock, lock_flags);

	asrc_priv->channel_avail += pair->channels;
	asrc_priv->pair[index] = NULL;
	pair->error = 0;

	spin_unlock_irqrestore(&asrc_priv->lock, lock_flags);
}