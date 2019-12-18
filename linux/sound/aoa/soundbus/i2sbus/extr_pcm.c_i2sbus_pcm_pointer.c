#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pcm_info {TYPE_2__* substream; scalar_t__ frame_count; } ;
struct i2sbus_dev {TYPE_1__* intfregs; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_6__ {scalar_t__ buffer_size; } ;
struct TYPE_5__ {TYPE_3__* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  frame_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_pcm_info (struct i2sbus_dev*,int,struct pcm_info**,int /*<<< orphan*/ *) ; 
 scalar_t__ in_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t i2sbus_pcm_pointer(struct i2sbus_dev *i2sdev, int in)
{
	struct pcm_info *pi;
	u32 fc;

	get_pcm_info(i2sdev, in, &pi, NULL);

	fc = in_le32(&i2sdev->intfregs->frame_count);
	fc = fc - pi->frame_count;

	if (fc >= pi->substream->runtime->buffer_size)
		fc %= pi->substream->runtime->buffer_size;
	return fc;
}