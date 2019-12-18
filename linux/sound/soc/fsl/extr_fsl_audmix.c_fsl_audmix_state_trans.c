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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct fsl_audmix_state {int tdms; int clk; int /*<<< orphan*/  msg; } ;
struct fsl_audmix {int tdms; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FSL_AUDMIX_CTR_MIXCLK (int) ; 
 unsigned int FSL_AUDMIX_CTR_MIXCLK_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct fsl_audmix* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int fsl_audmix_state_trans(struct snd_soc_component *comp,
				  unsigned int *mask, unsigned int *ctr,
				  const struct fsl_audmix_state prm)
{
	struct fsl_audmix *priv = snd_soc_component_get_drvdata(comp);
	/* Enforce all required TDMs are started */
	if ((priv->tdms & prm.tdms) != prm.tdms) {
		dev_dbg(comp->dev, "%s", prm.msg);
		return -EINVAL;
	}

	switch (prm.clk) {
	case 1:
	case 2:
		/* Set mix clock */
		(*mask) |= FSL_AUDMIX_CTR_MIXCLK_MASK;
		(*ctr)  |= FSL_AUDMIX_CTR_MIXCLK(prm.clk - 1);
		break;
	default:
		break;
	}

	return 0;
}