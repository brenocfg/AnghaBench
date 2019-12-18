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
typedef  int /*<<< orphan*/  u64 ;
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;
struct sst_byt_stream {int /*<<< orphan*/  pdata; int /*<<< orphan*/  (* notify_position ) (struct sst_byt_stream*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  running; } ;
struct sst_byt {struct sst_dsp* dsp; } ;

/* Variables and functions */
#define  IPC_IA_FW_INIT_CMPLT 129 
#define  IPC_SST_PERIOD_ELAPSED 128 
 int /*<<< orphan*/  SST_IPCD ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sst_byt_fw_ready (struct sst_byt*,int /*<<< orphan*/ ) ; 
 struct sst_byt_stream* sst_byt_get_stream (struct sst_byt*,int) ; 
 int sst_byt_header_msg_id (int /*<<< orphan*/ ) ; 
 int sst_byt_header_str_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_read64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sst_byt_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_byt_process_notification(struct sst_byt *byt,
					unsigned long *flags)
{
	struct sst_dsp *sst = byt->dsp;
	struct sst_byt_stream *stream;
	u64 header;
	u8 msg_id, stream_id;

	header = sst_dsp_shim_read64_unlocked(sst, SST_IPCD);
	msg_id = sst_byt_header_msg_id(header);

	switch (msg_id) {
	case IPC_SST_PERIOD_ELAPSED:
		stream_id = sst_byt_header_str_id(header);
		stream = sst_byt_get_stream(byt, stream_id);
		if (stream && stream->running && stream->notify_position) {
			spin_unlock_irqrestore(&sst->spinlock, *flags);
			stream->notify_position(stream, stream->pdata);
			spin_lock_irqsave(&sst->spinlock, *flags);
		}
		break;
	case IPC_IA_FW_INIT_CMPLT:
		sst_byt_fw_ready(byt, header);
		break;
	}

	return 1;
}