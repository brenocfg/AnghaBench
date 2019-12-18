#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int dummy; } ;
struct ec_param_codec_i2s {int dummy; } ;
struct cros_ec_device {int dummy; } ;
struct cros_ec_command {int outsize; int /*<<< orphan*/  data; scalar_t__ insize; int /*<<< orphan*/  command; scalar_t__ version; } ;
struct cros_ec_codec_data {struct cros_ec_device* ec_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_CODEC_I2S ; 
 int cros_ec_cmd_xfer_status (struct cros_ec_device*,struct cros_ec_command*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ec_param_codec_i2s*,int) ; 
 struct cros_ec_codec_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ec_command_no_resp(struct snd_soc_component *component,
			      struct ec_param_codec_i2s *param)
{
	struct cros_ec_codec_data *codec_data =
		snd_soc_component_get_drvdata(component);
	struct cros_ec_device *ec_device = codec_data->ec_device;
	u8 buffer[sizeof(struct cros_ec_command) +
		  sizeof(struct ec_param_codec_i2s)];
	struct cros_ec_command *msg = (struct cros_ec_command *)&buffer;

	msg->version = 0;
	msg->command = EC_CMD_CODEC_I2S;
	msg->outsize = sizeof(struct ec_param_codec_i2s);
	msg->insize = 0;

	memcpy(msg->data, param, msg->outsize);

	return cros_ec_cmd_xfer_status(ec_device, msg);
}