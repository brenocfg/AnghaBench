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
struct snd_soc_dai {struct device* dev; } ;
struct s3c_i2sv2_info {scalar_t__ regs; int /*<<< orphan*/  iis_pclk; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ S3C2412_IISMOD ; 
 unsigned int S3C2412_IISMOD_MODE_TXRX ; 
 int /*<<< orphan*/  clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c2412_snd_rxctrl (struct s3c_i2sv2_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2412_snd_txctrl (struct s3c_i2sv2_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct s3c_i2sv2_info*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

int s3c_i2sv2_probe(struct snd_soc_dai *dai,
		    struct s3c_i2sv2_info *i2s,
		    unsigned long base)
{
	struct device *dev = dai->dev;
	unsigned int iismod;

	i2s->dev = dev;

	/* record our i2s structure for later use in the callbacks */
	snd_soc_dai_set_drvdata(dai, i2s);

	i2s->iis_pclk = clk_get(dev, "iis");
	if (IS_ERR(i2s->iis_pclk)) {
		dev_err(dev, "failed to get iis_clock\n");
		return -ENOENT;
	}

	clk_prepare_enable(i2s->iis_pclk);

	/* Mark ourselves as in TXRX mode so we can run through our cleanup
	 * process without warnings. */
	iismod = readl(i2s->regs + S3C2412_IISMOD);
	iismod |= S3C2412_IISMOD_MODE_TXRX;
	writel(iismod, i2s->regs + S3C2412_IISMOD);
	s3c2412_snd_txctrl(i2s, 0);
	s3c2412_snd_rxctrl(i2s, 0);

	return 0;
}