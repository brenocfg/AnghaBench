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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct axg_fifo {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL1_FRDDR_FORCE_FINISH ; 
 int /*<<< orphan*/  FIFO_CTRL1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axg_fifo* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int g12a_frddr_dai_prepare(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct axg_fifo *fifo = snd_soc_dai_get_drvdata(dai);

	/* Reset the read pointer to the FIFO_INIT_ADDR */
	regmap_update_bits(fifo->map, FIFO_CTRL1,
			   CTRL1_FRDDR_FORCE_FINISH, 0);
	regmap_update_bits(fifo->map, FIFO_CTRL1,
			   CTRL1_FRDDR_FORCE_FINISH, CTRL1_FRDDR_FORCE_FINISH);
	regmap_update_bits(fifo->map, FIFO_CTRL1,
			   CTRL1_FRDDR_FORCE_FINISH, 0);

	return 0;
}