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
struct TYPE_4__ {TYPE_1__* properties; } ;
struct usb_line6_pod {int /*<<< orphan*/  monitor_level; TYPE_2__ line6; int /*<<< orphan*/  startup_work; int /*<<< orphan*/  startup_timer; } ;
struct usb_line6 {int /*<<< orphan*/  line6pcm; int /*<<< orphan*/  card; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  process_message; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LINE6_CAP_CONTROL ; 
 int /*<<< orphan*/  POD_SYSTEM_INVALID ; 
 int line6_init_midi (struct usb_line6*) ; 
 int line6_init_pcm (struct usb_line6*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_pod_disconnect ; 
 int /*<<< orphan*/  line6_pod_process_message ; 
 int /*<<< orphan*/  pod_control_monitor ; 
 int /*<<< orphan*/  pod_dev_attr_group ; 
 int /*<<< orphan*/  pod_pcm_properties ; 
 int /*<<< orphan*/  pod_startup1 (struct usb_line6_pod*) ; 
 int /*<<< orphan*/  pod_startup4 ; 
 int snd_card_add_dev_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pod_init(struct usb_line6 *line6,
		    const struct usb_device_id *id)
{
	int err;
	struct usb_line6_pod *pod = (struct usb_line6_pod *) line6;

	line6->process_message = line6_pod_process_message;
	line6->disconnect = line6_pod_disconnect;

	timer_setup(&pod->startup_timer, NULL, 0);
	INIT_WORK(&pod->startup_work, pod_startup4);

	/* create sysfs entries: */
	err = snd_card_add_dev_attr(line6->card, &pod_dev_attr_group);
	if (err < 0)
		return err;

	/* initialize MIDI subsystem: */
	err = line6_init_midi(line6);
	if (err < 0)
		return err;

	/* initialize PCM subsystem: */
	err = line6_init_pcm(line6, &pod_pcm_properties);
	if (err < 0)
		return err;

	/* register monitor control: */
	err = snd_ctl_add(line6->card,
			  snd_ctl_new1(&pod_control_monitor, line6->line6pcm));
	if (err < 0)
		return err;

	/*
	   When the sound card is registered at this point, the PODxt Live
	   displays "Invalid Code Error 07", so we do it later in the event
	   handler.
	 */

	if (pod->line6.properties->capabilities & LINE6_CAP_CONTROL) {
		pod->monitor_level = POD_SYSTEM_INVALID;

		/* initiate startup procedure: */
		pod_startup1(pod);
	}

	return 0;
}