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
struct most_dev {struct most_channel_config* conf; } ;
struct most_channel_config {int dummy; } ;
struct mbo {unsigned int processed_length; scalar_t__ virt_address; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int USB_MTU ; 
 unsigned int get_stream_frame_size (struct most_channel_config* const) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static int hdm_remove_padding(struct most_dev *mdev, int channel,
			      struct mbo *mbo)
{
	struct most_channel_config *const conf = &mdev->conf[channel];
	unsigned int frame_size = get_stream_frame_size(conf);
	unsigned int j, num_frames;

	if (!frame_size)
		return -EIO;
	num_frames = mbo->processed_length / USB_MTU;

	for (j = 1; j < num_frames; j++)
		memmove(mbo->virt_address + frame_size * j,
			mbo->virt_address + USB_MTU * j,
			frame_size);

	mbo->processed_length = frame_size * num_frames;
	return 0;
}