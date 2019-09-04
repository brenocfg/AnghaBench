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
struct tty_struct {struct snd_soc_component* disc_data; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* receive_buf ) (struct tty_struct*,unsigned char const*,char*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  pop_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_delta_hook_switch ; 
 int /*<<< orphan*/  ams_delta_hook_switch_pins ; 
 int /*<<< orphan*/  ams_delta_lock ; 
 int /*<<< orphan*/  ams_delta_muted ; 
 int cx81801_cmd_pending ; 
 int /*<<< orphan*/  cx81801_timeout ; 
 int /*<<< orphan*/  cx81801_timer ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_modem_codec ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int snd_soc_jack_add_pins (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ v253_ops ; 

__attribute__((used)) static void cx81801_receive(struct tty_struct *tty,
				const unsigned char *cp, char *fp, int count)
{
	struct snd_soc_component *component = tty->disc_data;
	const unsigned char *c;
	int apply, ret;

	if (!component)
		return;

	if (!component->card->pop_time) {
		/* First modem response, complete setup procedure */

		/* Initialize timer used for config pulse generation */
		timer_setup(&cx81801_timer, cx81801_timeout, 0);

		v253_ops.receive_buf(tty, cp, fp, count);

		/* Link hook switch to DAPM pins */
		ret = snd_soc_jack_add_pins(&ams_delta_hook_switch,
					ARRAY_SIZE(ams_delta_hook_switch_pins),
					ams_delta_hook_switch_pins);
		if (ret)
			dev_warn(component->dev,
				"Failed to link hook switch to DAPM pins, "
				"will continue with hook switch unlinked.\n");

		return;
	}

	v253_ops.receive_buf(tty, cp, fp, count);

	for (c = &cp[count - 1]; c >= cp; c--) {
		if (*c != '\r')
			continue;
		/* Complete modem response received, apply config to codec */

		spin_lock_bh(&ams_delta_lock);
		mod_timer(&cx81801_timer, jiffies + msecs_to_jiffies(150));
		apply = !ams_delta_muted && !cx81801_cmd_pending;
		cx81801_cmd_pending = 1;
		spin_unlock_bh(&ams_delta_lock);

		/* Apply config pulse by connecting the codec to the modem
		 * if not already done */
		if (apply)
			gpiod_set_value(gpiod_modem_codec, 1);
		break;
	}
}