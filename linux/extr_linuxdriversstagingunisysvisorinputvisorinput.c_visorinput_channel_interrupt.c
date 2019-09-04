#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct visorinput_devdata {struct input_dev* visorinput_dev; } ;
struct TYPE_2__ {int arg1; int action; int arg2; } ;
struct visor_inputreport {TYPE_1__ activity; } ;
struct visor_device {int /*<<< orphan*/  visorchannel; int /*<<< orphan*/  device; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
#define  INPUTACTION_KEY_DOWN 138 
#define  INPUTACTION_KEY_DOWN_UP 137 
#define  INPUTACTION_KEY_UP 136 
#define  INPUTACTION_MOUSE_BUTTON_CLICK 135 
#define  INPUTACTION_MOUSE_BUTTON_DCLICK 134 
#define  INPUTACTION_MOUSE_BUTTON_DOWN 133 
#define  INPUTACTION_MOUSE_BUTTON_UP 132 
#define  INPUTACTION_SET_LOCKING_KEY_STATE 131 
#define  INPUTACTION_WHEEL_ROTATE_AWAY 130 
#define  INPUTACTION_WHEEL_ROTATE_TOWARD 129 
#define  INPUTACTION_XY_MOTION 128 
 int /*<<< orphan*/  REL_WHEEL ; 
 int calc_button (int) ; 
 struct visorinput_devdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_locking_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int scancode_to_keycode (int) ; 
 int /*<<< orphan*/  visorchannel_signalremove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct visor_inputreport*) ; 

__attribute__((used)) static void visorinput_channel_interrupt(struct visor_device *dev)
{
	struct visor_inputreport r;
	int scancode, keycode;
	struct input_dev *visorinput_dev;
	int xmotion, ymotion, button;
	int i;
	struct visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	if (!devdata)
		return;

	visorinput_dev = devdata->visorinput_dev;

	while (!visorchannel_signalremove(dev->visorchannel, 0, &r)) {
		scancode = r.activity.arg1;
		keycode = scancode_to_keycode(scancode);
		switch (r.activity.action) {
		case INPUTACTION_KEY_DOWN:
			input_report_key(visorinput_dev, keycode, 1);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_KEY_UP:
			input_report_key(visorinput_dev, keycode, 0);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_KEY_DOWN_UP:
			input_report_key(visorinput_dev, keycode, 1);
			input_sync(visorinput_dev);
			input_report_key(visorinput_dev, keycode, 0);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_SET_LOCKING_KEY_STATE:
			handle_locking_key(visorinput_dev, keycode,
					   r.activity.arg2);
			break;
		case INPUTACTION_XY_MOTION:
			xmotion = r.activity.arg1;
			ymotion = r.activity.arg2;
			input_report_abs(visorinput_dev, ABS_X, xmotion);
			input_report_abs(visorinput_dev, ABS_Y, ymotion);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_MOUSE_BUTTON_DOWN:
			button = calc_button(r.activity.arg1);
			if (button < 0)
				break;
			input_report_key(visorinput_dev, button, 1);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_MOUSE_BUTTON_UP:
			button = calc_button(r.activity.arg1);
			if (button < 0)
				break;
			input_report_key(visorinput_dev, button, 0);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_MOUSE_BUTTON_CLICK:
			button = calc_button(r.activity.arg1);
			if (button < 0)
				break;
			input_report_key(visorinput_dev, button, 1);
			input_sync(visorinput_dev);
			input_report_key(visorinput_dev, button, 0);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_MOUSE_BUTTON_DCLICK:
			button = calc_button(r.activity.arg1);
			if (button < 0)
				break;
			for (i = 0; i < 2; i++) {
				input_report_key(visorinput_dev, button, 1);
				input_sync(visorinput_dev);
				input_report_key(visorinput_dev, button, 0);
				input_sync(visorinput_dev);
			}
			break;
		case INPUTACTION_WHEEL_ROTATE_AWAY:
			input_report_rel(visorinput_dev, REL_WHEEL, 1);
			input_sync(visorinput_dev);
			break;
		case INPUTACTION_WHEEL_ROTATE_TOWARD:
			input_report_rel(visorinput_dev, REL_WHEEL, -1);
			input_sync(visorinput_dev);
			break;
		default:
			/* Unsupported input action */
			break;
		}
	}
}