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
struct zx_spdif_info {int /*<<< orphan*/  dai_clk; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct zx_spdif_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_spdif_startup(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	struct zx_spdif_info *zx_spdif = dev_get_drvdata(dai->dev);

	return clk_prepare_enable(zx_spdif->dai_clk);
}