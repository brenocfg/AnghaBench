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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  num; } ;
struct ec_response_lightbar {TYPE_1__ version; } ;
struct ec_params_lightbar {int /*<<< orphan*/  cmd; } ;
struct cros_ec_dev {int /*<<< orphan*/  ec_dev; } ;
struct cros_ec_command {int result; scalar_t__ data; } ;

/* Variables and functions */
#define  EC_RES_INVALID_PARAM 129 
#define  EC_RES_SUCCESS 128 
 int /*<<< orphan*/  LIGHTBAR_CMD_VERSION ; 
 struct cros_ec_command* alloc_lightbar_cmd_msg (struct cros_ec_dev*) ; 
 int cros_ec_cmd_xfer (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 

__attribute__((used)) static int get_lightbar_version(struct cros_ec_dev *ec,
				uint32_t *ver_ptr, uint32_t *flg_ptr)
{
	struct ec_params_lightbar *param;
	struct ec_response_lightbar *resp;
	struct cros_ec_command *msg;
	int ret;

	msg = alloc_lightbar_cmd_msg(ec);
	if (!msg)
		return 0;

	param = (struct ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_VERSION;
	ret = cros_ec_cmd_xfer(ec->ec_dev, msg);
	if (ret < 0) {
		ret = 0;
		goto exit;
	}

	switch (msg->result) {
	case EC_RES_INVALID_PARAM:
		/* Pixel had no version command. */
		if (ver_ptr)
			*ver_ptr = 0;
		if (flg_ptr)
			*flg_ptr = 0;
		ret = 1;
		goto exit;

	case EC_RES_SUCCESS:
		resp = (struct ec_response_lightbar *)msg->data;

		/* Future devices w/lightbars should implement this command */
		if (ver_ptr)
			*ver_ptr = resp->version.num;
		if (flg_ptr)
			*flg_ptr = resp->version.flags;
		ret = 1;
		goto exit;
	}

	/* Anything else (ie, EC_RES_INVALID_COMMAND) - no lightbar */
	ret = 0;
exit:
	kfree(msg);
	return ret;
}