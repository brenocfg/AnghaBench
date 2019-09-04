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
struct mite_channel {scalar_t__ dir; } ;
struct comedi_subdevice {int dummy; } ;

/* Variables and functions */
 scalar_t__ COMEDI_INPUT ; 
 int /*<<< orphan*/  mite_sync_input_dma (struct mite_channel*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  mite_sync_output_dma (struct mite_channel*,struct comedi_subdevice*) ; 

void mite_sync_dma(struct mite_channel *mite_chan, struct comedi_subdevice *s)
{
	if (mite_chan->dir == COMEDI_INPUT)
		mite_sync_input_dma(mite_chan, s);
	else
		mite_sync_output_dma(mite_chan, s);
}