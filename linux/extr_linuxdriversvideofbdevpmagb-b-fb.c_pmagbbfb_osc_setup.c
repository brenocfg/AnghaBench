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
typedef  int u32 ;
struct tc_bus {int dummy; } ;
struct pmagbbfb_par {int osc0; int osc1; } ;
struct TYPE_3__ {int pixclock; } ;
struct fb_info {TYPE_1__ var; int /*<<< orphan*/  device; struct pmagbbfb_par* par; } ;
struct TYPE_4__ {struct tc_bus* bus; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  SFB_REG_TCCLK_COUNT ; 
 int /*<<< orphan*/  SFB_REG_VIDCLK_COUNT ; 
 int /*<<< orphan*/  gp0_write (struct pmagbbfb_par*,int) ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ sfb_read (struct pmagbbfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_write (struct pmagbbfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tc_get_speed (struct tc_bus*) ; 
 TYPE_2__* to_tc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pmagbbfb_osc_setup(struct fb_info *info)
{
	static unsigned int pmagbbfb_freqs[] = {
		130808, 119843, 104000, 92980, 74370, 72800,
		69197, 66000, 65000, 50350, 36000, 32000, 25175
	};
	struct pmagbbfb_par *par = info->par;
	struct tc_bus *tbus = to_tc_dev(info->device)->bus;
	u32 count0 = 8, count1 = 8, counttc = 16 * 256 + 8;
	u32 freq0, freq1, freqtc = tc_get_speed(tbus) / 250;
	int i, j;

	gp0_write(par, 0);				/* select Osc0 */
	for (j = 0; j < 16; j++) {
		mb();
		sfb_write(par, SFB_REG_TCCLK_COUNT, 0);
		mb();
		for (i = 0; i < 100; i++) {	/* nominally max. 20.5us */
			if (sfb_read(par, SFB_REG_TCCLK_COUNT) == 0)
				break;
			udelay(1);
		}
		count0 += sfb_read(par, SFB_REG_VIDCLK_COUNT);
	}

	gp0_write(par, 1);				/* select Osc1 */
	for (j = 0; j < 16; j++) {
		mb();
		sfb_write(par, SFB_REG_TCCLK_COUNT, 0);

		for (i = 0; i < 100; i++) {	/* nominally max. 20.5us */
			if (sfb_read(par, SFB_REG_TCCLK_COUNT) == 0)
				break;
			udelay(1);
		}
		count1 += sfb_read(par, SFB_REG_VIDCLK_COUNT);
	}

	freq0 = (freqtc * count0 + counttc / 2) / counttc;
	par->osc0 = freq0;
	if (freq0 >= pmagbbfb_freqs[0] - (pmagbbfb_freqs[0] + 32) / 64 &&
	    freq0 <= pmagbbfb_freqs[0] + (pmagbbfb_freqs[0] + 32) / 64)
		par->osc0 = pmagbbfb_freqs[0];

	freq1 = (par->osc0 * count1 + count0 / 2) / count0;
	par->osc1 = freq1;
	for (i = 0; i < ARRAY_SIZE(pmagbbfb_freqs); i++)
		if (freq1 >= pmagbbfb_freqs[i] -
			     (pmagbbfb_freqs[i] + 128) / 256 &&
		    freq1 <= pmagbbfb_freqs[i] +
			     (pmagbbfb_freqs[i] + 128) / 256) {
			par->osc1 = pmagbbfb_freqs[i];
			break;
		}

	if (par->osc0 - par->osc1 <= (par->osc0 + par->osc1 + 256) / 512 ||
	    par->osc1 - par->osc0 <= (par->osc0 + par->osc1 + 256) / 512)
		par->osc1 = 0;

	gp0_write(par, par->osc1 != 0);			/* reselect OscX */

	info->var.pixclock = par->osc1 ?
			     (1000000000 + par->osc1 / 2) / par->osc1 :
			     (1000000000 + par->osc0 / 2) / par->osc0;
}