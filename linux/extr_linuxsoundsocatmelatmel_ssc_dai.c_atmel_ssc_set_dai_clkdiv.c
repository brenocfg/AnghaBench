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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct platform_device {size_t id; } ;
struct atmel_ssc_info {int dir_mask; int cmr_div; int tcmr_period; int rcmr_period; int /*<<< orphan*/  forced_divider; } ;

/* Variables and functions */
#define  ATMEL_SSC_CMR_DIV 130 
#define  ATMEL_SSC_RCMR_PERIOD 129 
#define  ATMEL_SSC_TCMR_PERIOD 128 
 int /*<<< orphan*/  BIT (int const) ; 
 int EBUSY ; 
 int EINVAL ; 
 int SSC_DIR_MASK_CAPTURE ; 
 int SSC_DIR_MASK_PLAYBACK ; 
 struct atmel_ssc_info* ssc_info ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_ssc_set_dai_clkdiv(struct snd_soc_dai *cpu_dai,
	int div_id, int div)
{
	struct platform_device *pdev = to_platform_device(cpu_dai->dev);
	struct atmel_ssc_info *ssc_p = &ssc_info[pdev->id];

	switch (div_id) {
	case ATMEL_SSC_CMR_DIV:
		/*
		 * The same master clock divider is used for both
		 * transmit and receive, so if a value has already
		 * been set, it must match this value.
		 */
		if (ssc_p->dir_mask !=
			(SSC_DIR_MASK_PLAYBACK | SSC_DIR_MASK_CAPTURE))
			ssc_p->cmr_div = div;
		else if (ssc_p->cmr_div == 0)
			ssc_p->cmr_div = div;
		else
			if (div != ssc_p->cmr_div)
				return -EBUSY;
		ssc_p->forced_divider |= BIT(ATMEL_SSC_CMR_DIV);
		break;

	case ATMEL_SSC_TCMR_PERIOD:
		ssc_p->tcmr_period = div;
		ssc_p->forced_divider |= BIT(ATMEL_SSC_TCMR_PERIOD);
		break;

	case ATMEL_SSC_RCMR_PERIOD:
		ssc_p->rcmr_period = div;
		ssc_p->forced_divider |= BIT(ATMEL_SSC_RCMR_PERIOD);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}