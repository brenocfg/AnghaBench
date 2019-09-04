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
struct davinci_spi {int /*<<< orphan*/  done; int /*<<< orphan*/  wcount; int /*<<< orphan*/  rcount; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SPIINT ; 
 int /*<<< orphan*/  SPIINT_MASKINT ; 
 int /*<<< orphan*/  clear_io_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int davinci_spi_process_events (struct davinci_spi*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t davinci_spi_irq(s32 irq, void *data)
{
	struct davinci_spi *dspi = data;
	int status;

	status = davinci_spi_process_events(dspi);
	if (unlikely(status != 0))
		clear_io_bits(dspi->base + SPIINT, SPIINT_MASKINT);

	if ((!dspi->rcount && !dspi->wcount) || status)
		complete(&dspi->done);

	return IRQ_HANDLED;
}