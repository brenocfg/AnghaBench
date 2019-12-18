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
typedef  char u8 ;
typedef  int u32 ;
struct sst_hsw_ipc_fw_ready {int fw_info_size; scalar_t__* fw_info; int /*<<< orphan*/  outbox_size; int /*<<< orphan*/  outbox_offset; int /*<<< orphan*/  inbox_size; int /*<<< orphan*/  inbox_offset; } ;
struct sst_hsw {int boot_complete; int /*<<< orphan*/  dev; int /*<<< orphan*/  boot_wait; int /*<<< orphan*/  dsp; } ;
typedef  int /*<<< orphan*/  fw_ready ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  IPC_MAX_MAILBOX_BYTES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  sst_dsp_mailbox_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_read (int /*<<< orphan*/ ,struct sst_hsw_ipc_fw_ready*,int,int) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsw_fw_ready(struct sst_hsw *hsw, u32 header)
{
	struct sst_hsw_ipc_fw_ready fw_ready;
	u32 offset;
	u8 fw_info[IPC_MAX_MAILBOX_BYTES - 5 * sizeof(u32)];
	char *tmp[5], *pinfo;
	int i = 0;

	offset = (header & 0x1FFFFFFF) << 3;

	dev_dbg(hsw->dev, "ipc: DSP is ready 0x%8.8x offset %d\n",
		header, offset);

	/* copy data from the DSP FW ready offset */
	sst_dsp_read(hsw->dsp, &fw_ready, offset, sizeof(fw_ready));

	sst_dsp_mailbox_init(hsw->dsp, fw_ready.inbox_offset,
		fw_ready.inbox_size, fw_ready.outbox_offset,
		fw_ready.outbox_size);

	hsw->boot_complete = true;
	wake_up(&hsw->boot_wait);

	dev_dbg(hsw->dev, " mailbox upstream 0x%x - size 0x%x\n",
		fw_ready.inbox_offset, fw_ready.inbox_size);
	dev_dbg(hsw->dev, " mailbox downstream 0x%x - size 0x%x\n",
		fw_ready.outbox_offset, fw_ready.outbox_size);
	if (fw_ready.fw_info_size < sizeof(fw_ready.fw_info)) {
		fw_ready.fw_info[fw_ready.fw_info_size] = 0;
		dev_dbg(hsw->dev, " Firmware info: %s \n", fw_ready.fw_info);

		/* log the FW version info got from the mailbox here. */
		memcpy(fw_info, fw_ready.fw_info, fw_ready.fw_info_size);
		pinfo = &fw_info[0];
		for (i = 0; i < ARRAY_SIZE(tmp); i++)
			tmp[i] = strsep(&pinfo, " ");
		dev_info(hsw->dev, "FW loaded, mailbox readback FW info: type %s, - "
			"version: %s.%s, build %s, source commit id: %s\n",
			tmp[0], tmp[1], tmp[2], tmp[3], tmp[4]);
	}
}