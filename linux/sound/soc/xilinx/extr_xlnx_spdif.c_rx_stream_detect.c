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
struct spdif_dev_data {int rx_chsts_updated; int /*<<< orphan*/  chsts_q; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_STATUS_UPDATE_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct spdif_dev_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int rx_stream_detect(struct snd_soc_dai *dai)
{
	int err;
	struct spdif_dev_data *ctx = dev_get_drvdata(dai->dev);
	unsigned long jiffies = msecs_to_jiffies(CH_STATUS_UPDATE_TIMEOUT);

	/* start capture only if stream is detected within 40ms timeout */
	err = wait_event_interruptible_timeout(ctx->chsts_q,
					       ctx->rx_chsts_updated,
					       jiffies);
	if (!err) {
		dev_err(dai->dev, "No streaming audio detected!\n");
		return -EINVAL;
	}
	ctx->rx_chsts_updated = false;

	return 0;
}