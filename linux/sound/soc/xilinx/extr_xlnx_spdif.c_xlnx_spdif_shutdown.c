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
struct spdif_dev_data {scalar_t__ base; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 scalar_t__ XSPDIF_SOFT_RESET_REG ; 
 int /*<<< orphan*/  XSPDIF_SOFT_RESET_VALUE ; 
 struct spdif_dev_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xlnx_spdif_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct spdif_dev_data *ctx = dev_get_drvdata(dai->dev);

	writel(XSPDIF_SOFT_RESET_VALUE, ctx->base + XSPDIF_SOFT_RESET_REG);
}