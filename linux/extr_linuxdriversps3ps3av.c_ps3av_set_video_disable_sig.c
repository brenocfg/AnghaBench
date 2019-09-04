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
struct TYPE_3__ {int num_of_hdmi; int num_of_avmulti; } ;
struct TYPE_4__ {int /*<<< orphan*/ * av_port; TYPE_1__ av_hw_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3AV_CMD_MUTE_OFF ; 
 int /*<<< orphan*/  PS3AV_CMD_MUTE_ON ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* ps3av ; 
 int ps3av_cmd_av_tv_mute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ps3av_cmd_av_video_disable_sig (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps3av_set_video_disable_sig(void)
{
	int i, num_of_hdmi_port, num_of_av_port, res;

	num_of_hdmi_port = ps3av->av_hw_conf.num_of_hdmi;
	num_of_av_port = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmulti;

	/* tv mute */
	for (i = 0; i < num_of_hdmi_port; i++) {
		res = ps3av_cmd_av_tv_mute(ps3av->av_port[i],
					   PS3AV_CMD_MUTE_ON);
		if (res < 0)
			return -1;
	}
	msleep(100);

	/* video mute on */
	for (i = 0; i < num_of_av_port; i++) {
		res = ps3av_cmd_av_video_disable_sig(ps3av->av_port[i]);
		if (res < 0)
			return -1;
		if (i < num_of_hdmi_port) {
			res = ps3av_cmd_av_tv_mute(ps3av->av_port[i],
						   PS3AV_CMD_MUTE_OFF);
			if (res < 0)
				return -1;
		}
	}
	msleep(300);

	return 0;
}