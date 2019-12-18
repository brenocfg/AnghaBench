#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sof_ipc_window_elem {int type; scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ offset; } ;
struct snd_sof_dev {scalar_t__* bar; int /*<<< orphan*/  dev; TYPE_2__ stream_box; int /*<<< orphan*/  dsp_oops_offset; TYPE_1__* info_window; } ;
struct TYPE_3__ {int num_windows; struct sof_ipc_window_elem* window; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOF_DEBUGFS_ACCESS_D0_ONLY ; 
 int /*<<< orphan*/  SOF_FW_BLK_TYPE_SRAM ; 
#define  SOF_IPC_REGION_DEBUG 134 
#define  SOF_IPC_REGION_DOWNBOX 133 
#define  SOF_IPC_REGION_EXCEPTION 132 
#define  SOF_IPC_REGION_REGS 131 
#define  SOF_IPC_REGION_STREAM 130 
#define  SOF_IPC_REGION_TRACE 129 
#define  SOF_IPC_REGION_UPBOX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_debugfs_io_item (struct snd_sof_dev*,scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_get_bar_index (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_get_window_offset (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_mailbox_init (struct snd_sof_dev*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sof_get_windows(struct snd_sof_dev *sdev)
{
	struct sof_ipc_window_elem *elem;
	u32 outbox_offset = 0;
	u32 stream_offset = 0;
	u32 inbox_offset = 0;
	u32 outbox_size = 0;
	u32 stream_size = 0;
	u32 inbox_size = 0;
	int window_offset;
	int bar;
	int i;

	if (!sdev->info_window) {
		dev_err(sdev->dev, "error: have no window info\n");
		return;
	}

	bar = snd_sof_dsp_get_bar_index(sdev, SOF_FW_BLK_TYPE_SRAM);
	if (bar < 0) {
		dev_err(sdev->dev, "error: have no bar mapping\n");
		return;
	}

	for (i = 0; i < sdev->info_window->num_windows; i++) {
		elem = &sdev->info_window->window[i];

		window_offset = snd_sof_dsp_get_window_offset(sdev, elem->id);
		if (window_offset < 0) {
			dev_warn(sdev->dev, "warn: no offset for window %d\n",
				 elem->id);
			continue;
		}

		switch (elem->type) {
		case SOF_IPC_REGION_UPBOX:
			inbox_offset = window_offset + elem->offset;
			inbox_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						inbox_offset,
						elem->size, "inbox",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		case SOF_IPC_REGION_DOWNBOX:
			outbox_offset = window_offset + elem->offset;
			outbox_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						outbox_offset,
						elem->size, "outbox",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		case SOF_IPC_REGION_TRACE:
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						window_offset +
						elem->offset,
						elem->size, "etrace",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		case SOF_IPC_REGION_DEBUG:
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						window_offset +
						elem->offset,
						elem->size, "debug",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		case SOF_IPC_REGION_STREAM:
			stream_offset = window_offset + elem->offset;
			stream_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						stream_offset,
						elem->size, "stream",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		case SOF_IPC_REGION_REGS:
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						window_offset +
						elem->offset,
						elem->size, "regs",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		case SOF_IPC_REGION_EXCEPTION:
			sdev->dsp_oops_offset = window_offset + elem->offset;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						window_offset +
						elem->offset,
						elem->size, "exception",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			break;
		default:
			dev_err(sdev->dev, "error: get illegal window info\n");
			return;
		}
	}

	if (outbox_size == 0 || inbox_size == 0) {
		dev_err(sdev->dev, "error: get illegal mailbox window\n");
		return;
	}

	snd_sof_dsp_mailbox_init(sdev, inbox_offset, inbox_size,
				 outbox_offset, outbox_size);
	sdev->stream_box.offset = stream_offset;
	sdev->stream_box.size = stream_size;

	dev_dbg(sdev->dev, " mailbox upstream 0x%x - size 0x%x\n",
		inbox_offset, inbox_size);
	dev_dbg(sdev->dev, " mailbox downstream 0x%x - size 0x%x\n",
		outbox_offset, outbox_size);
	dev_dbg(sdev->dev, " stream region 0x%x - size 0x%x\n",
		stream_offset, stream_size);
}