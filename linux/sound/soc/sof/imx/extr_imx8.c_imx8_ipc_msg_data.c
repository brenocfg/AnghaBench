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
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct snd_sof_dev {TYPE_1__ dsp_box; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sof_mailbox_read (struct snd_sof_dev*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void imx8_ipc_msg_data(struct snd_sof_dev *sdev,
			      struct snd_pcm_substream *substream,
			      void *p, size_t sz)
{
	sof_mailbox_read(sdev, sdev->dsp_box.offset, p, sz);
}