#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ regs; int /*<<< orphan*/  iis_clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2410_GPE (int /*<<< orphan*/ ) ; 
 scalar_t__ S3C2410_IISCON ; 
 int /*<<< orphan*/  S3C2410_IISCON_IISEN ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ s3c24xx_i2s ; 
 int /*<<< orphan*/  s3c24xx_i2s_pcm_stereo_in ; 
 int /*<<< orphan*/  s3c24xx_i2s_pcm_stereo_out ; 
 int /*<<< orphan*/  s3c24xx_snd_rxctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c24xx_snd_txctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_cfgall_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_i2s_probe(struct snd_soc_dai *dai)
{
	int ret;
	snd_soc_dai_init_dma_data(dai, &s3c24xx_i2s_pcm_stereo_out,
					&s3c24xx_i2s_pcm_stereo_in);

	s3c24xx_i2s.iis_clk = devm_clk_get(dai->dev, "iis");
	if (IS_ERR(s3c24xx_i2s.iis_clk)) {
		pr_err("failed to get iis_clock\n");
		return PTR_ERR(s3c24xx_i2s.iis_clk);
	}
	ret = clk_prepare_enable(s3c24xx_i2s.iis_clk);
	if (ret)
		return ret;

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	writel(S3C2410_IISCON_IISEN, s3c24xx_i2s.regs + S3C2410_IISCON);

	s3c24xx_snd_txctrl(0);
	s3c24xx_snd_rxctrl(0);

	return 0;
}