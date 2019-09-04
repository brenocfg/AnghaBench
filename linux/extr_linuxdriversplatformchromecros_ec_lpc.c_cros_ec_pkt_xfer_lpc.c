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
typedef  scalar_t__ u8 ;
struct ec_host_response {int data_len; int /*<<< orphan*/  checksum; scalar_t__ result; } ;
struct cros_ec_device {int /*<<< orphan*/  dev; scalar_t__* dout; } ;
struct cros_ec_command {int insize; scalar_t__* data; scalar_t__ result; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ EC_COMMAND_PROTOCOL_3 ; 
 scalar_t__ EC_LPC_ADDR_HOST_CMD ; 
 scalar_t__ EC_LPC_ADDR_HOST_DATA ; 
 scalar_t__ EC_LPC_ADDR_HOST_PACKET ; 
 int EIO ; 
 int EMSGSIZE ; 
 int cros_ec_check_result (struct cros_ec_device*,struct cros_ec_command*) ; 
 scalar_t__ cros_ec_lpc_read_bytes (scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  cros_ec_lpc_write_bytes (scalar_t__,int,scalar_t__*) ; 
 int cros_ec_prepare_tx (struct cros_ec_device*,struct cros_ec_command*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ec_response_timed_out () ; 

__attribute__((used)) static int cros_ec_pkt_xfer_lpc(struct cros_ec_device *ec,
				struct cros_ec_command *msg)
{
	struct ec_host_response response;
	u8 sum;
	int ret = 0;
	u8 *dout;

	ret = cros_ec_prepare_tx(ec, msg);

	/* Write buffer */
	cros_ec_lpc_write_bytes(EC_LPC_ADDR_HOST_PACKET, ret, ec->dout);

	/* Here we go */
	sum = EC_COMMAND_PROTOCOL_3;
	cros_ec_lpc_write_bytes(EC_LPC_ADDR_HOST_CMD, 1, &sum);

	if (ec_response_timed_out()) {
		dev_warn(ec->dev, "EC responsed timed out\n");
		ret = -EIO;
		goto done;
	}

	/* Check result */
	msg->result = cros_ec_lpc_read_bytes(EC_LPC_ADDR_HOST_DATA, 1, &sum);
	ret = cros_ec_check_result(ec, msg);
	if (ret)
		goto done;

	/* Read back response */
	dout = (u8 *)&response;
	sum = cros_ec_lpc_read_bytes(EC_LPC_ADDR_HOST_PACKET, sizeof(response),
				     dout);

	msg->result = response.result;

	if (response.data_len > msg->insize) {
		dev_err(ec->dev,
			"packet too long (%d bytes, expected %d)",
			response.data_len, msg->insize);
		ret = -EMSGSIZE;
		goto done;
	}

	/* Read response and process checksum */
	sum += cros_ec_lpc_read_bytes(EC_LPC_ADDR_HOST_PACKET +
				      sizeof(response), response.data_len,
				      msg->data);

	if (sum) {
		dev_err(ec->dev,
			"bad packet checksum %02x\n",
			response.checksum);
		ret = -EBADMSG;
		goto done;
	}

	/* Return actual amount of data received */
	ret = response.data_len;
done:
	return ret;
}