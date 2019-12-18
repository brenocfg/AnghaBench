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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ cmd; int size; } ;
struct sof_ipc_ext_data_hdr {int type; TYPE_1__ hdr; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  SOF_IPC_EXT_DMA_BUFFER 129 
#define  SOF_IPC_EXT_WINDOW 128 
 scalar_t__ SOF_IPC_FW_READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int get_ext_windows (struct snd_sof_dev*,struct sof_ipc_ext_data_hdr*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_block_read (struct snd_sof_dev*,int,int,void*,int) ; 

int snd_sof_fw_parse_ext_data(struct snd_sof_dev *sdev, u32 bar, u32 offset)
{
	struct sof_ipc_ext_data_hdr *ext_hdr;
	void *ext_data;
	int ret = 0;

	ext_data = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!ext_data)
		return -ENOMEM;

	/* get first header */
	snd_sof_dsp_block_read(sdev, bar, offset, ext_data,
			       sizeof(*ext_hdr));
	ext_hdr = ext_data;

	while (ext_hdr->hdr.cmd == SOF_IPC_FW_READY) {
		/* read in ext structure */
		offset += sizeof(*ext_hdr);
		snd_sof_dsp_block_read(sdev, bar, offset,
				   (void *)((u8 *)ext_data + sizeof(*ext_hdr)),
				   ext_hdr->hdr.size - sizeof(*ext_hdr));

		dev_dbg(sdev->dev, "found ext header type %d size 0x%x\n",
			ext_hdr->type, ext_hdr->hdr.size);

		/* process structure data */
		switch (ext_hdr->type) {
		case SOF_IPC_EXT_DMA_BUFFER:
			break;
		case SOF_IPC_EXT_WINDOW:
			ret = get_ext_windows(sdev, ext_hdr);
			break;
		default:
			break;
		}

		if (ret < 0) {
			dev_err(sdev->dev, "error: failed to parse ext data type %d\n",
				ext_hdr->type);
			break;
		}

		/* move to next header */
		offset += ext_hdr->hdr.size;
		snd_sof_dsp_block_read(sdev, bar, offset, ext_data,
				       sizeof(*ext_hdr));
		ext_hdr = ext_data;
	}

	kfree(ext_data);
	return ret;
}