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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9335_ANA_AMIC1 ; 
 int /*<<< orphan*/  WCD9335_ANA_AMIC3 ; 
 int /*<<< orphan*/  WCD9335_ANA_AMIC5 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u16 wcd9335_codec_get_amic_pwlvl_reg(struct snd_soc_component *comp,
					    int amic)
{
	u16 pwr_level_reg = 0;

	switch (amic) {
	case 1:
	case 2:
		pwr_level_reg = WCD9335_ANA_AMIC1;
		break;

	case 3:
	case 4:
		pwr_level_reg = WCD9335_ANA_AMIC3;
		break;

	case 5:
	case 6:
		pwr_level_reg = WCD9335_ANA_AMIC5;
		break;
	default:
		dev_err(comp->dev, "invalid amic: %d\n", amic);
		break;
	}

	return pwr_level_reg;
}