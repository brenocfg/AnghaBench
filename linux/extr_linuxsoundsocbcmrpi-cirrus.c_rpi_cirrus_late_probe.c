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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; int /*<<< orphan*/  codec_dai; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct rpi_cirrus_priv {int /*<<< orphan*/ * iec958_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct snd_soc_pcm_runtime* get_wm5102_runtime (struct snd_soc_card*) ; 
 struct snd_soc_pcm_runtime* get_wm8804_runtime (struct snd_soc_card*) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_dai_set_sysclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_cirrus_late_probe(struct snd_soc_card *card)
{
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_pcm_runtime *wm5102_runtime = get_wm5102_runtime(card);
	struct snd_soc_pcm_runtime *wm8804_runtime = get_wm8804_runtime(card);
	int ret;

	dev_dbg(card->dev, "iec958_bits: %02x %02x %02x %02x\n",
		priv->iec958_status[0],
		priv->iec958_status[1],
		priv->iec958_status[2],
		priv->iec958_status[3]);

	ret = snd_soc_dai_set_sysclk(
		wm5102_runtime->codec_dai, ARIZONA_CLK_SYSCLK, 0, 0);
	if (ret) {
		dev_err(card->dev,
			"Failed to set WM5102 codec dai clk domain: %d\n", ret);
		return ret;
	}

	ret = snd_soc_dai_set_sysclk(
		wm8804_runtime->cpu_dai, ARIZONA_CLK_SYSCLK, 0, 0);
	if (ret)
		dev_err(card->dev,
			"Failed to set WM8804 codec dai clk domain: %d\n", ret);

	return ret;
}