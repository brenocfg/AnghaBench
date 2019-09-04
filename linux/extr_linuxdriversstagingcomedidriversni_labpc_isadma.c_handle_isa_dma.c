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
struct labpc_private {int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;TYPE_1__* dma; } ;
struct comedi_isadma_desc {scalar_t__ size; } ;
struct comedi_device {struct labpc_private* private; } ;
struct TYPE_2__ {struct comedi_isadma_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMATC_CLEAR_REG ; 
 int /*<<< orphan*/  comedi_isadma_program (struct comedi_isadma_desc*) ; 
 int /*<<< orphan*/  labpc_drain_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_isa_dma(struct comedi_device *dev)
{
	struct labpc_private *devpriv = dev->private;
	struct comedi_isadma_desc *desc = &devpriv->dma->desc[0];

	labpc_drain_dma(dev);

	if (desc->size)
		comedi_isadma_program(desc);

	/* clear dma tc interrupt */
	devpriv->write_byte(dev, 0x1, DMATC_CLEAR_REG);
}