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
struct mmal_buffer {int /*<<< orphan*/ * dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_vchi_buffer_cleanup (struct mmal_buffer*) ; 

__attribute__((used)) static int bcm2835_codec_mmal_buf_cleanup(struct mmal_buffer *mmal_buf)
{
	mmal_vchi_buffer_cleanup(mmal_buf);

	if (mmal_buf->dma_buf) {
		dma_buf_put(mmal_buf->dma_buf);
		mmal_buf->dma_buf = NULL;
	}

	return 0;
}