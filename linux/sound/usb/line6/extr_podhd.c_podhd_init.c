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
struct TYPE_4__ {TYPE_1__* properties; int /*<<< orphan*/  ifcdev; } ;
struct usb_line6_podhd {TYPE_2__ line6; } ;
struct usb_line6 {int /*<<< orphan*/  startup_work; int /*<<< orphan*/  card; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  startup; int /*<<< orphan*/  disconnect; } ;
struct usb_interface {int dummy; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct TYPE_3__ {int capabilities; int /*<<< orphan*/  ctrl_if; } ;

/* Variables and functions */
 int ENODEV ; 
 int LINE6_CAP_CONTROL ; 
 int LINE6_CAP_CONTROL_INFO ; 
 int LINE6_CAP_PCM ; 
 scalar_t__ LINE6_PODX3 ; 
 scalar_t__ LINE6_PODX3LIVE ; 
 int /*<<< orphan*/  PODHD_STARTUP_DELAY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int line6_init_pcm (struct usb_line6*,int /*<<< orphan*/ *) ; 
 struct usb_line6_podhd* line6_to_podhd (struct usb_line6*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  podhd_dev_attr_group ; 
 int /*<<< orphan*/  podhd_disconnect ; 
 int /*<<< orphan*/  podhd_driver ; 
 int /*<<< orphan*/  podhd_pcm_properties ; 
 int /*<<< orphan*/  podhd_startup ; 
 int /*<<< orphan*/  podx3_pcm_properties ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_card_add_dev_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int usb_driver_claim_interface (int /*<<< orphan*/ *,struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int podhd_init(struct usb_line6 *line6,
		      const struct usb_device_id *id)
{
	int err;
	struct usb_line6_podhd *pod = line6_to_podhd(line6);
	struct usb_interface *intf;

	line6->disconnect = podhd_disconnect;
	line6->startup = podhd_startup;

	if (pod->line6.properties->capabilities & LINE6_CAP_CONTROL) {
		/* claim the data interface */
		intf = usb_ifnum_to_if(line6->usbdev,
					pod->line6.properties->ctrl_if);
		if (!intf) {
			dev_err(pod->line6.ifcdev, "interface %d not found\n",
				pod->line6.properties->ctrl_if);
			return -ENODEV;
		}

		err = usb_driver_claim_interface(&podhd_driver, intf, NULL);
		if (err != 0) {
			dev_err(pod->line6.ifcdev, "can't claim interface %d, error %d\n",
				pod->line6.properties->ctrl_if, err);
			return err;
		}
	}

	if (pod->line6.properties->capabilities & LINE6_CAP_CONTROL_INFO) {
		/* create sysfs entries: */
		err = snd_card_add_dev_attr(line6->card, &podhd_dev_attr_group);
		if (err < 0)
			return err;
	}

	if (pod->line6.properties->capabilities & LINE6_CAP_PCM) {
		/* initialize PCM subsystem: */
		err = line6_init_pcm(line6,
			(id->driver_info == LINE6_PODX3 ||
			id->driver_info == LINE6_PODX3LIVE) ? &podx3_pcm_properties :
			&podhd_pcm_properties);
		if (err < 0)
			return err;
	}

	if (!(pod->line6.properties->capabilities & LINE6_CAP_CONTROL_INFO)) {
		/* register USB audio system directly */
		return snd_card_register(line6->card);
	}

	/* init device and delay registering */
	schedule_delayed_work(&line6->startup_work,
			      msecs_to_jiffies(PODHD_STARTUP_DELAY));
	return 0;
}