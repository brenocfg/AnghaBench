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
typedef  void* u8 ;
typedef  int u16 ;
struct sst_data {TYPE_1__* pdev; struct snd_sst_bytes_v2* byte_stream; } ;
struct snd_sst_bytes_v2 {int len; int /*<<< orphan*/  bytes; void* pipe_id; void* task_id; void* block; void* ipc_msg; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  SST_CMD_BYTES_SET ; 
 int SST_MAX_BIN_BYTES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,struct snd_sst_bytes_v2*,int) ; 

__attribute__((used)) static int sst_fill_byte_control(struct sst_data *drv,
					 u8 ipc_msg, u8 block,
					 u8 task_id, u8 pipe_id,
					 u16 len, void *cmd_data)
{
	struct snd_sst_bytes_v2 *byte_data = drv->byte_stream;

	byte_data->type = SST_CMD_BYTES_SET;
	byte_data->ipc_msg = ipc_msg;
	byte_data->block = block;
	byte_data->task_id = task_id;
	byte_data->pipe_id = pipe_id;

	if (len > SST_MAX_BIN_BYTES - sizeof(*byte_data)) {
		dev_err(&drv->pdev->dev, "command length too big (%u)", len);
		return -EINVAL;
	}
	byte_data->len = len;
	memcpy(byte_data->bytes, cmd_data, len);
	print_hex_dump_bytes("writing to lpe: ", DUMP_PREFIX_OFFSET,
			     byte_data, len + sizeof(*byte_data));
	return 0;
}