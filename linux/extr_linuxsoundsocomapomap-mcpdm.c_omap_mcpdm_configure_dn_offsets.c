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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct omap_mcpdm {int dn_rx_offset; } ;

/* Variables and functions */
 int MCPDM_DNOFST_RX1 (int /*<<< orphan*/ ) ; 
 int MCPDM_DNOFST_RX2 (int /*<<< orphan*/ ) ; 
 struct omap_mcpdm* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

void omap_mcpdm_configure_dn_offsets(struct snd_soc_pcm_runtime *rtd,
				    u8 rx1, u8 rx2)
{
	struct omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(rtd->cpu_dai);

	mcpdm->dn_rx_offset = MCPDM_DNOFST_RX1(rx1) | MCPDM_DNOFST_RX2(rx2);
}