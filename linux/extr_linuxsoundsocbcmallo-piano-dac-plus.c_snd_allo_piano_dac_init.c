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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; struct glb_pool* drvdata; } ;
struct glb_pool {int dual_mode; int /*<<< orphan*/  lock; scalar_t__ set_mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ digital_gain_0db_limit ; 
 struct glb_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_limit_volume (struct snd_soc_card*,char*,int) ; 

__attribute__((used)) static int snd_allo_piano_dac_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct glb_pool *glb_ptr;

	glb_ptr = kzalloc(sizeof(struct glb_pool), GFP_KERNEL);
	if (!glb_ptr)
		return -ENOMEM;

	card->drvdata = glb_ptr;
	glb_ptr->dual_mode = 2;
	glb_ptr->set_mode = 0;

	mutex_init(&glb_ptr->lock);

	if (digital_gain_0db_limit) {
		int ret;

		ret = snd_soc_limit_volume(card, "Digital Playback Volume",
					207);
		if (ret < 0)
			dev_warn(card->dev, "Failed to set volume limit: %d\n",
				ret);
	}
	return 0;
}