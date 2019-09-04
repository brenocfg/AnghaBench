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
typedef  int u8 ;
struct cros_ec_device {int proto_version; int* dout; } ;
struct cros_ec_command {int outsize; int version; int command; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EC_CMD_VERSION0 ; 
 int EC_MSG_TX_HEADER_BYTES ; 
 int EC_MSG_TX_PROTO_BYTES ; 
 int EC_PROTO2_MAX_PARAM_SIZE ; 
 int prepare_packet (struct cros_ec_device*,struct cros_ec_command*) ; 

int cros_ec_prepare_tx(struct cros_ec_device *ec_dev,
		       struct cros_ec_command *msg)
{
	u8 *out;
	u8 csum;
	int i;

	if (ec_dev->proto_version > 2)
		return prepare_packet(ec_dev, msg);

	BUG_ON(msg->outsize > EC_PROTO2_MAX_PARAM_SIZE);
	out = ec_dev->dout;
	out[0] = EC_CMD_VERSION0 + msg->version;
	out[1] = msg->command;
	out[2] = msg->outsize;
	csum = out[0] + out[1] + out[2];
	for (i = 0; i < msg->outsize; i++)
		csum += out[EC_MSG_TX_HEADER_BYTES + i] = msg->data[i];
	out[EC_MSG_TX_HEADER_BYTES + msg->outsize] = csum;

	return EC_MSG_TX_PROTO_BYTES + msg->outsize;
}