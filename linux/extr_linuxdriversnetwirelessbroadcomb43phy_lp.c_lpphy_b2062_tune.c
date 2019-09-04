#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int crystalfreq; } ;
struct TYPE_10__ {TYPE_4__ pmu; } ;
struct ssb_bus {TYPE_5__ chipco; } ;
struct TYPE_6__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_3__* dev; TYPE_1__ phy; } ;
struct b43_phy_lp {int pdiv; } ;
struct b206x_channel {unsigned int channel; int* data; } ;
struct TYPE_8__ {TYPE_2__* sdev; } ;
struct TYPE_7__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct b206x_channel*) ; 
 int /*<<< orphan*/  B2062_N_LGENA_CTL5 ; 
 int /*<<< orphan*/  B2062_N_LGENA_CTL6 ; 
 int /*<<< orphan*/  B2062_N_LGENA_TUNE0 ; 
 int /*<<< orphan*/  B2062_N_LGENA_TUNE2 ; 
 int /*<<< orphan*/  B2062_N_LGENA_TUNE3 ; 
 int /*<<< orphan*/  B2062_N_TX_PAD ; 
 int /*<<< orphan*/  B2062_N_TX_PGA ; 
 int /*<<< orphan*/  B2062_N_TX_TUNE ; 
 int /*<<< orphan*/  B2062_S_LGENG_CTL1 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL14 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL19 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL23 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL24 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL26 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL27 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL28 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL29 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL3 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL33 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL34 ; 
 scalar_t__ B43_WARN_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 struct b206x_channel* b2062_chantbl ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int channel2freq_lp (unsigned int) ; 
 int /*<<< orphan*/  lpphy_b2062_reset_pll_bias (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_b2062_vco_calib (struct b43_wldev*) ; 

__attribute__((used)) static int lpphy_b2062_tune(struct b43_wldev *dev,
			    unsigned int channel)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	struct ssb_bus *bus = dev->dev->sdev->bus;
	const struct b206x_channel *chandata = NULL;
	u32 crystal_freq = bus->chipco.pmu.crystalfreq * 1000;
	u32 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
	int i, err = 0;

	for (i = 0; i < ARRAY_SIZE(b2062_chantbl); i++) {
		if (b2062_chantbl[i].channel == channel) {
			chandata = &b2062_chantbl[i];
			break;
		}
	}

	if (B43_WARN_ON(!chandata))
		return -EINVAL;

	b43_radio_set(dev, B2062_S_RFPLL_CTL14, 0x04);
	b43_radio_write(dev, B2062_N_LGENA_TUNE0, chandata->data[0]);
	b43_radio_write(dev, B2062_N_LGENA_TUNE2, chandata->data[1]);
	b43_radio_write(dev, B2062_N_LGENA_TUNE3, chandata->data[2]);
	b43_radio_write(dev, B2062_N_TX_TUNE, chandata->data[3]);
	b43_radio_write(dev, B2062_S_LGENG_CTL1, chandata->data[4]);
	b43_radio_write(dev, B2062_N_LGENA_CTL5, chandata->data[5]);
	b43_radio_write(dev, B2062_N_LGENA_CTL6, chandata->data[6]);
	b43_radio_write(dev, B2062_N_TX_PGA, chandata->data[7]);
	b43_radio_write(dev, B2062_N_TX_PAD, chandata->data[8]);

	tmp1 = crystal_freq / 1000;
	tmp2 = lpphy->pdiv * 1000;
	b43_radio_write(dev, B2062_S_RFPLL_CTL33, 0xCC);
	b43_radio_write(dev, B2062_S_RFPLL_CTL34, 0x07);
	lpphy_b2062_reset_pll_bias(dev);
	tmp3 = tmp2 * channel2freq_lp(channel);
	if (channel2freq_lp(channel) < 4000)
		tmp3 *= 2;
	tmp4 = 48 * tmp1;
	tmp6 = tmp3 / tmp4;
	tmp7 = tmp3 % tmp4;
	b43_radio_write(dev, B2062_S_RFPLL_CTL26, tmp6);
	tmp5 = tmp7 * 0x100;
	tmp6 = tmp5 / tmp4;
	tmp7 = tmp5 % tmp4;
	b43_radio_write(dev, B2062_S_RFPLL_CTL27, tmp6);
	tmp5 = tmp7 * 0x100;
	tmp6 = tmp5 / tmp4;
	tmp7 = tmp5 % tmp4;
	b43_radio_write(dev, B2062_S_RFPLL_CTL28, tmp6);
	tmp5 = tmp7 * 0x100;
	tmp6 = tmp5 / tmp4;
	tmp7 = tmp5 % tmp4;
	b43_radio_write(dev, B2062_S_RFPLL_CTL29, tmp6 + ((2 * tmp7) / tmp4));
	tmp8 = b43_radio_read(dev, B2062_S_RFPLL_CTL19);
	tmp9 = ((2 * tmp3 * (tmp8 + 1)) + (3 * tmp1)) / (6 * tmp1);
	b43_radio_write(dev, B2062_S_RFPLL_CTL23, (tmp9 >> 8) + 16);
	b43_radio_write(dev, B2062_S_RFPLL_CTL24, tmp9 & 0xFF);

	lpphy_b2062_vco_calib(dev);
	if (b43_radio_read(dev, B2062_S_RFPLL_CTL3) & 0x10) {
		b43_radio_write(dev, B2062_S_RFPLL_CTL33, 0xFC);
		b43_radio_write(dev, B2062_S_RFPLL_CTL34, 0);
		lpphy_b2062_reset_pll_bias(dev);
		lpphy_b2062_vco_calib(dev);
		if (b43_radio_read(dev, B2062_S_RFPLL_CTL3) & 0x10)
			err = -EIO;
	}

	b43_radio_mask(dev, B2062_S_RFPLL_CTL14, ~0x04);
	return err;
}