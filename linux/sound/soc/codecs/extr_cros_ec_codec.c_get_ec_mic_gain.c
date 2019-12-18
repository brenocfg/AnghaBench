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
struct ec_param_codec_i2s {int /*<<< orphan*/  cmd; } ;
struct ec_codec_i2s_gain {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CODEC_GET_GAIN ; 
 int ec_command_get_gain (struct snd_soc_component*,struct ec_param_codec_i2s*,struct ec_codec_i2s_gain*) ; 

__attribute__((used)) static int get_ec_mic_gain(struct snd_soc_component *component,
			   u8 *left, u8 *right)
{
	struct ec_param_codec_i2s param;
	struct ec_codec_i2s_gain resp;
	int ret;

	param.cmd = EC_CODEC_GET_GAIN;

	ret = ec_command_get_gain(component, &param, &resp);
	if (ret < 0)
		return ret;

	*left = resp.left;
	*right = resp.right;

	return 0;
}