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
typedef  int u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct omap_dmic {int threshold; int /*<<< orphan*/  clk_div; int /*<<< orphan*/  latency; int /*<<< orphan*/  pm_qos_req; } ;

/* Variables and functions */
 int OMAP_DMICOUTFORMAT_LJUST ; 
 int OMAP_DMIC_CLK_DIV (int /*<<< orphan*/ ) ; 
 int OMAP_DMIC_CLK_DIV_MASK ; 
 int /*<<< orphan*/  OMAP_DMIC_CTRL_REG ; 
 int /*<<< orphan*/  OMAP_DMIC_FIFO_CTRL_REG ; 
 int OMAP_DMIC_FORMAT ; 
 int OMAP_DMIC_POLAR1 ; 
 int OMAP_DMIC_POLAR2 ; 
 int OMAP_DMIC_POLAR3 ; 
 int OMAP_DMIC_POLAR_MASK ; 
 int omap_dmic_read (struct omap_dmic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dmic_write (struct omap_dmic*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pm_qos_request_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct omap_dmic* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_dmic_dai_prepare(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);
	u32 ctrl;

	if (pm_qos_request_active(&dmic->pm_qos_req))
		pm_qos_update_request(&dmic->pm_qos_req, dmic->latency);

	/* Configure uplink threshold */
	omap_dmic_write(dmic, OMAP_DMIC_FIFO_CTRL_REG, dmic->threshold);

	ctrl = omap_dmic_read(dmic, OMAP_DMIC_CTRL_REG);

	/* Set dmic out format */
	ctrl &= ~(OMAP_DMIC_FORMAT | OMAP_DMIC_POLAR_MASK);
	ctrl |= (OMAP_DMICOUTFORMAT_LJUST | OMAP_DMIC_POLAR1 |
		 OMAP_DMIC_POLAR2 | OMAP_DMIC_POLAR3);

	/* Configure dmic clock divider */
	ctrl &= ~OMAP_DMIC_CLK_DIV_MASK;
	ctrl |= OMAP_DMIC_CLK_DIV(dmic->clk_div);

	omap_dmic_write(dmic, OMAP_DMIC_CTRL_REG, ctrl);

	omap_dmic_write(dmic, OMAP_DMIC_CTRL_REG,
			ctrl | OMAP_DMICOUTFORMAT_LJUST | OMAP_DMIC_POLAR1 |
			OMAP_DMIC_POLAR2 | OMAP_DMIC_POLAR3);

	return 0;
}