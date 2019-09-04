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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct pn544_i2c_fw_frame_write {int* be_dest_addr; int /*<<< orphan*/  data; int /*<<< orphan*/  be_datalen; int /*<<< orphan*/  be_length; int /*<<< orphan*/  cmd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PN544_FW_CMD_WRITE ; 
 int PN544_FW_I2C_MAX_PAYLOAD ; 
 scalar_t__ PN544_FW_I2C_WRITE_DATA_MAX_LEN ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_be16 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pn544_hci_i2c_fw_write_cmd(struct i2c_client *client, u32 dest_addr,
				      const u8 *data, u16 datalen)
{
	u8 frame[PN544_FW_I2C_MAX_PAYLOAD];
	struct pn544_i2c_fw_frame_write *framep;
	u16 params_len;
	int framelen;
	int r;

	if (datalen > PN544_FW_I2C_WRITE_DATA_MAX_LEN)
		datalen = PN544_FW_I2C_WRITE_DATA_MAX_LEN;

	framep = (struct pn544_i2c_fw_frame_write *) frame;

	params_len = sizeof(framep->be_dest_addr) +
		     sizeof(framep->be_datalen) + datalen;
	framelen = params_len + sizeof(framep->cmd) +
			     sizeof(framep->be_length);

	framep->cmd = PN544_FW_CMD_WRITE;

	put_unaligned_be16(params_len, &framep->be_length);

	framep->be_dest_addr[0] = (dest_addr & 0xff0000) >> 16;
	framep->be_dest_addr[1] = (dest_addr & 0xff00) >> 8;
	framep->be_dest_addr[2] = dest_addr & 0xff;

	put_unaligned_be16(datalen, &framep->be_datalen);

	memcpy(framep->data, data, datalen);

	r = i2c_master_send(client, frame, framelen);

	if (r == framelen)
		return datalen;
	else if (r < 0)
		return r;
	else
		return -EIO;
}