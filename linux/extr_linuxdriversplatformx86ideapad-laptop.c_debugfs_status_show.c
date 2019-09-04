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
struct seq_file {struct ideapad_private* private; } ;
struct ideapad_private {TYPE_1__* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CONSERVATION_BIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  VPCCMD_R_3G ; 
 int /*<<< orphan*/  VPCCMD_R_BL ; 
 int /*<<< orphan*/  VPCCMD_R_BL_MAX ; 
 int /*<<< orphan*/  VPCCMD_R_BL_POWER ; 
 int /*<<< orphan*/  VPCCMD_R_BT ; 
 int /*<<< orphan*/  VPCCMD_R_CAMERA ; 
 int /*<<< orphan*/  VPCCMD_R_RF ; 
 int /*<<< orphan*/  VPCCMD_R_TOUCHPAD ; 
 int /*<<< orphan*/  VPCCMD_R_WIFI ; 
 int /*<<< orphan*/  method_gbmd (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int debugfs_status_show(struct seq_file *s, void *data)
{
	struct ideapad_private *priv = s->private;
	unsigned long value;

	if (!priv)
		return -EINVAL;

	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BL_MAX, &value))
		seq_printf(s, "Backlight max:\t%lu\n", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BL, &value))
		seq_printf(s, "Backlight now:\t%lu\n", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &value))
		seq_printf(s, "BL power value:\t%s\n", value ? "On" : "Off");
	seq_printf(s, "=====================\n");

	if (!read_ec_data(priv->adev->handle, VPCCMD_R_RF, &value))
		seq_printf(s, "Radio status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_WIFI, &value))
		seq_printf(s, "Wifi status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BT, &value))
		seq_printf(s, "BT status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_3G, &value))
		seq_printf(s, "3G status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	seq_printf(s, "=====================\n");

	if (!read_ec_data(priv->adev->handle, VPCCMD_R_TOUCHPAD, &value))
		seq_printf(s, "Touchpad status:%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_CAMERA, &value))
		seq_printf(s, "Camera status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	seq_puts(s, "=====================\n");

	if (!method_gbmd(priv->adev->handle, &value)) {
		seq_printf(s, "Conservation mode:\t%s(%lu)\n",
			   test_bit(BM_CONSERVATION_BIT, &value) ? "On" : "Off",
			   value);
	}

	return 0;
}