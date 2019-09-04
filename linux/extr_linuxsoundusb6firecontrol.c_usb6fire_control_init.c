#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sfire_chip {struct control_runtime* control; TYPE_1__* dev; int /*<<< orphan*/  card; struct comm_runtime* comm; } ;
struct control_runtime {int /*<<< orphan*/  set_channels; int /*<<< orphan*/  set_rate; int /*<<< orphan*/  (* update_streaming ) (struct control_runtime*) ;struct sfire_chip* chip; } ;
struct comm_runtime {int /*<<< orphan*/  (* write8 ) (struct comm_runtime*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; scalar_t__ type; } ;
struct TYPE_6__ {scalar_t__ name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* elements ; 
 TYPE_3__* init_data ; 
 int /*<<< orphan*/  kfree (struct control_runtime*) ; 
 struct control_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mute_elements ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (TYPE_2__*,struct control_runtime*) ; 
 int /*<<< orphan*/  stub1 (struct comm_runtime*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb6fire_control_add_virtual (struct control_runtime*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb6fire_control_input_vol_update (struct control_runtime*) ; 
 int /*<<< orphan*/  usb6fire_control_line_phono_update (struct control_runtime*) ; 
 int /*<<< orphan*/  usb6fire_control_opt_coax_update (struct control_runtime*) ; 
 int /*<<< orphan*/  usb6fire_control_output_mute_update (struct control_runtime*) ; 
 int /*<<< orphan*/  usb6fire_control_output_vol_update (struct control_runtime*) ; 
 int /*<<< orphan*/  usb6fire_control_set_channels ; 
 int /*<<< orphan*/  usb6fire_control_set_rate ; 
 int /*<<< orphan*/  usb6fire_control_streaming_update (struct control_runtime*) ; 
 int /*<<< orphan*/  vol_elements ; 

int usb6fire_control_init(struct sfire_chip *chip)
{
	int i;
	int ret;
	struct control_runtime *rt = kzalloc(sizeof(struct control_runtime),
			GFP_KERNEL);
	struct comm_runtime *comm_rt = chip->comm;

	if (!rt)
		return -ENOMEM;

	rt->chip = chip;
	rt->update_streaming = usb6fire_control_streaming_update;
	rt->set_rate = usb6fire_control_set_rate;
	rt->set_channels = usb6fire_control_set_channels;

	i = 0;
	while (init_data[i].type) {
		comm_rt->write8(comm_rt, init_data[i].type, init_data[i].reg,
				init_data[i].value);
		i++;
	}

	usb6fire_control_opt_coax_update(rt);
	usb6fire_control_line_phono_update(rt);
	usb6fire_control_output_vol_update(rt);
	usb6fire_control_output_mute_update(rt);
	usb6fire_control_input_vol_update(rt);
	usb6fire_control_streaming_update(rt);

	ret = usb6fire_control_add_virtual(rt, chip->card,
		"Master Playback Volume", vol_elements);
	if (ret) {
		dev_err(&chip->dev->dev, "cannot add control.\n");
		kfree(rt);
		return ret;
	}
	ret = usb6fire_control_add_virtual(rt, chip->card,
		"Master Playback Switch", mute_elements);
	if (ret) {
		dev_err(&chip->dev->dev, "cannot add control.\n");
		kfree(rt);
		return ret;
	}

	i = 0;
	while (elements[i].name) {
		ret = snd_ctl_add(chip->card, snd_ctl_new1(&elements[i], rt));
		if (ret < 0) {
			kfree(rt);
			dev_err(&chip->dev->dev, "cannot add control.\n");
			return ret;
		}
		i++;
	}

	chip->control = rt;
	return 0;
}