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
struct dt282x_private {int /*<<< orphan*/  dma_dir; struct comedi_isadma* dma; } ;
struct comedi_isadma_desc {int size; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; } ;
struct comedi_device {struct dt282x_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_isadma_program (struct comedi_isadma_desc*) ; 
 int /*<<< orphan*/  comedi_isadma_set_mode (struct comedi_isadma_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt282x_prep_ao_dma(struct comedi_device *dev, int dma_index, int n)
{
	struct dt282x_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[dma_index];

	desc->size = n;
	comedi_isadma_set_mode(desc, devpriv->dma_dir);

	comedi_isadma_program(desc);

	return n;
}