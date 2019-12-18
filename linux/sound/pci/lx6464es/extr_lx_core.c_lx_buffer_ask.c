#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int* cmd; int* stat; int stat_len; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_2__ rmh; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BF_EOB ; 
 int BF_VALID ; 
 int BUFF_FLAGS_OFFSET ; 
 int /*<<< orphan*/  CMD_08_ASK_BUFFERS ; 
 int MASK_DATA_SIZE ; 
 int MAX_STREAM_BUFFER ; 
 int PIPE_INFO_TO_CMD (int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_buffer_ask(struct lx6464es *chip, u32 pipe, int is_capture,
		  u32 *r_needed, u32 *r_freed, u32 *size_array)
{
	int err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

#ifdef CONFIG_SND_DEBUG
	if (size_array)
		memset(size_array, 0, sizeof(u32)*MAX_STREAM_BUFFER);
#endif

	*r_needed = 0;
	*r_freed = 0;

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_08_ASK_BUFFERS);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	if (!err) {
		int i;
		for (i = 0; i < MAX_STREAM_BUFFER; ++i) {
			u32 stat = chip->rmh.stat[i];
			if (stat & (BF_EOB << BUFF_FLAGS_OFFSET)) {
				/* finished */
				*r_freed += 1;
				if (size_array)
					size_array[i] = stat & MASK_DATA_SIZE;
			} else if ((stat & (BF_VALID << BUFF_FLAGS_OFFSET))
				   == 0)
				/* free */
				*r_needed += 1;
		}

		dev_dbg(chip->card->dev,
			"CMD_08_ASK_BUFFERS: needed %d, freed %d\n",
			    *r_needed, *r_freed);
		for (i = 0; i < MAX_STREAM_BUFFER; ++i) {
			for (i = 0; i != chip->rmh.stat_len; ++i)
				dev_dbg(chip->card->dev,
					"  stat[%d]: %x, %x\n", i,
					    chip->rmh.stat[i],
					    chip->rmh.stat[i] & MASK_DATA_SIZE);
		}
	}

	mutex_unlock(&chip->msg_lock);
	return err;
}