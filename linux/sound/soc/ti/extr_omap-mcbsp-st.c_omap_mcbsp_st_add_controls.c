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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct omap_mcbsp {int /*<<< orphan*/  dev; int /*<<< orphan*/  st_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_mcbsp2_st_controls ; 
 int /*<<< orphan*/  omap_mcbsp3_st_controls ; 
 int snd_soc_add_dai_controls (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_mcbsp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

int omap_mcbsp_st_add_controls(struct snd_soc_pcm_runtime *rtd, int port_id)
{
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);

	if (!mcbsp->st_data) {
		dev_warn(mcbsp->dev, "No sidetone data for port\n");
		return 0;
	}

	switch (port_id) {
	case 2: /* McBSP 2 */
		return snd_soc_add_dai_controls(cpu_dai,
					omap_mcbsp2_st_controls,
					ARRAY_SIZE(omap_mcbsp2_st_controls));
	case 3: /* McBSP 3 */
		return snd_soc_add_dai_controls(cpu_dai,
					omap_mcbsp3_st_controls,
					ARRAY_SIZE(omap_mcbsp3_st_controls));
	default:
		dev_err(mcbsp->dev, "Port %d not supported\n", port_id);
		break;
	}

	return -EINVAL;
}