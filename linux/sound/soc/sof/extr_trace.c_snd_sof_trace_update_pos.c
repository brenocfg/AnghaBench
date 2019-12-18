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
struct sof_ipc_dma_trace_posn {scalar_t__ host_offset; scalar_t__ overflow; int /*<<< orphan*/  messages; } ;
struct snd_sof_dev {scalar_t__ host_offset; int /*<<< orphan*/  dev; int /*<<< orphan*/  trace_sleep; scalar_t__ dtrace_is_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int snd_sof_trace_update_pos(struct snd_sof_dev *sdev,
			     struct sof_ipc_dma_trace_posn *posn)
{
	if (sdev->dtrace_is_enabled && sdev->host_offset != posn->host_offset) {
		sdev->host_offset = posn->host_offset;
		wake_up(&sdev->trace_sleep);
	}

	if (posn->overflow != 0)
		dev_err(sdev->dev,
			"error: DSP trace buffer overflow %u bytes. Total messages %d\n",
			posn->overflow, posn->messages);

	return 0;
}