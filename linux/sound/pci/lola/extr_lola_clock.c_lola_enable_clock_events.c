#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nid; } ;
struct lola {TYPE_2__* card; TYPE_1__ clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int LOLA_UNSOLICITED_ENABLE ; 
 int LOLA_UNSOLICITED_TAG ; 
 int /*<<< orphan*/  LOLA_VERB_SET_UNSOLICITED_ENABLE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int lola_codec_read (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 

int lola_enable_clock_events(struct lola *chip)
{
	unsigned int res;
	int err;

	err = lola_codec_read(chip, chip->clock.nid,
			      LOLA_VERB_SET_UNSOLICITED_ENABLE,
			      LOLA_UNSOLICITED_ENABLE | LOLA_UNSOLICITED_TAG,
			      0, &res, NULL);
	if (err < 0)
		return err;
	if (res) {
		dev_warn(chip->card->dev, "error in enable_clock_events %d\n",
		       res);
		return -EINVAL;
	}
	return 0;
}