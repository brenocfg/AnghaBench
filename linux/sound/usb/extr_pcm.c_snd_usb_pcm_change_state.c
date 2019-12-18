#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_substream {TYPE_3__* str_pd; TYPE_2__* dev; TYPE_1__* stream; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int snd_usb_power_domain_set (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

__attribute__((used)) static int snd_usb_pcm_change_state(struct snd_usb_substream *subs, int state)
{
	int ret;

	if (!subs->str_pd)
		return 0;

	ret = snd_usb_power_domain_set(subs->stream->chip, subs->str_pd, state);
	if (ret < 0) {
		dev_err(&subs->dev->dev,
			"Cannot change Power Domain ID: %d to state: %d. Err: %d\n",
			subs->str_pd->pd_id, state, ret);
		return ret;
	}

	return 0;
}