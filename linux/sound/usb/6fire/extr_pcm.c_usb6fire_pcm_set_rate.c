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
struct pcm_runtime {size_t rate; int /*<<< orphan*/  out_packet_size; int /*<<< orphan*/  in_packet_size; int /*<<< orphan*/  out_n_analog; int /*<<< orphan*/  in_n_analog; TYPE_2__* chip; } ;
struct control_runtime {int usb_streaming; int (* update_streaming ) (struct control_runtime*) ;int (* set_rate ) (struct control_runtime*,size_t) ;int (* set_channels ) (struct control_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_4__ {TYPE_1__* dev; struct control_runtime* control; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_N_CHANNELS ; 
 int /*<<< orphan*/  OUT_N_CHANNELS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rates ; 
 int /*<<< orphan*/ * rates_in_packet_size ; 
 int /*<<< orphan*/ * rates_out_packet_size ; 
 int stub1 (struct control_runtime*) ; 
 int stub2 (struct control_runtime*,size_t) ; 
 int stub3 (struct control_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (struct control_runtime*) ; 

__attribute__((used)) static int usb6fire_pcm_set_rate(struct pcm_runtime *rt)
{
	int ret;
	struct control_runtime *ctrl_rt = rt->chip->control;

	ctrl_rt->usb_streaming = false;
	ret = ctrl_rt->update_streaming(ctrl_rt);
	if (ret < 0) {
		dev_err(&rt->chip->dev->dev,
			"error stopping streaming while setting samplerate %d.\n",
			rates[rt->rate]);
		return ret;
	}

	ret = ctrl_rt->set_rate(ctrl_rt, rt->rate);
	if (ret < 0) {
		dev_err(&rt->chip->dev->dev,
			"error setting samplerate %d.\n",
			rates[rt->rate]);
		return ret;
	}

	ret = ctrl_rt->set_channels(ctrl_rt, OUT_N_CHANNELS, IN_N_CHANNELS,
			false, false);
	if (ret < 0) {
		dev_err(&rt->chip->dev->dev,
			"error initializing channels while setting samplerate %d.\n",
			rates[rt->rate]);
		return ret;
	}

	ctrl_rt->usb_streaming = true;
	ret = ctrl_rt->update_streaming(ctrl_rt);
	if (ret < 0) {
		dev_err(&rt->chip->dev->dev,
			"error starting streaming while setting samplerate %d.\n",
			rates[rt->rate]);
		return ret;
	}

	rt->in_n_analog = IN_N_CHANNELS;
	rt->out_n_analog = OUT_N_CHANNELS;
	rt->in_packet_size = rates_in_packet_size[rt->rate];
	rt->out_packet_size = rates_out_packet_size[rt->rate];
	return 0;
}