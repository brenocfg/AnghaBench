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
typedef  int u32 ;
struct echoaudio {int pipe_alloc_mask; int pipe_cyclic_mask; TYPE_2__* comm_page; TYPE_1__* card; scalar_t__ bad_board; } ;
struct audiopipe {int index; int interleave; scalar_t__* dma_counter; int /*<<< orphan*/  state; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_4__ {scalar_t__* position; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  PIPE_STATE_STOPPED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int allocate_pipes(struct echoaudio *chip, struct audiopipe *pipe,
			  int pipe_index, int interleave)
{
	int i;
	u32 channel_mask;

	dev_dbg(chip->card->dev,
		"allocate_pipes: ch=%d int=%d\n", pipe_index, interleave);

	if (chip->bad_board)
		return -EIO;

	for (channel_mask = i = 0; i < interleave; i++)
		channel_mask |= 1 << (pipe_index + i);
	if (chip->pipe_alloc_mask & channel_mask) {
		dev_err(chip->card->dev,
			"allocate_pipes: channel already open\n");
		return -EAGAIN;
	}

	chip->comm_page->position[pipe_index] = 0;
	chip->pipe_alloc_mask |= channel_mask;
	/* This driver uses cyclic buffers only */
	chip->pipe_cyclic_mask |= channel_mask;
	pipe->index = pipe_index;
	pipe->interleave = interleave;
	pipe->state = PIPE_STATE_STOPPED;

	/* The counter register is where the DSP writes the 32 bit DMA
	position for a pipe.  The DSP is constantly updating this value as
	it moves data. The DMA counter is in units of bytes, not samples. */
	pipe->dma_counter = (__le32 *)&chip->comm_page->position[pipe_index];
	*pipe->dma_counter = 0;
	return pipe_index;
}