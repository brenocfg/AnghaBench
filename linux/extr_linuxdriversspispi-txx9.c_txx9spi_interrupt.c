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
struct txx9spi {int /*<<< orphan*/  waitq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TXx9_SPCR0 ; 
 int TXx9_SPCR0_RBSIE ; 
 int txx9spi_rd (struct txx9spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txx9spi_wr (struct txx9spi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t txx9spi_interrupt(int irq, void *dev_id)
{
	struct txx9spi *c = dev_id;

	/* disable rx intr */
	txx9spi_wr(c, txx9spi_rd(c, TXx9_SPCR0) & ~TXx9_SPCR0_RBSIE,
			TXx9_SPCR0);
	wake_up(&c->waitq);
	return IRQ_HANDLED;
}