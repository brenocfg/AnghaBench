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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct hi6210_i2s {int clocks; int /*<<< orphan*/  sysctrl; int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  SC_PERIPH_RSTEN1 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct hi6210_i2s* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hi6210_i2s_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *cpu_dai)
{
	struct hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	int n;

	for (n = 0; n < i2s->clocks; n++)
		clk_disable_unprepare(i2s->clk[n]);

	regmap_write(i2s->sysctrl, SC_PERIPH_RSTEN1, BIT(5));
}