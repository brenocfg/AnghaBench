#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; } ;
struct fsi_master {TYPE_1__ fsib; TYPE_1__ fsia; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AB_IO (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AI_SHIFT ; 
 int /*<<< orphan*/  AO_SHIFT ; 
 int /*<<< orphan*/  BI_SHIFT ; 
 int /*<<< orphan*/  BO_SHIFT ; 
 int /*<<< orphan*/  IR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SOFT_RST ; 
 int /*<<< orphan*/  fsi_count_fifo_err (TYPE_1__*) ; 
 int /*<<< orphan*/  fsi_irq_clear_status (TYPE_1__*) ; 
 int fsi_irq_get_status (struct fsi_master*) ; 
 int /*<<< orphan*/  fsi_master_mask_set (struct fsi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_stream_transfer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fsi_interrupt(int irq, void *data)
{
	struct fsi_master *master = data;
	u32 int_st = fsi_irq_get_status(master);

	/* clear irq status */
	fsi_master_mask_set(master, SOFT_RST, IR, 0);
	fsi_master_mask_set(master, SOFT_RST, IR, IR);

	if (int_st & AB_IO(1, AO_SHIFT))
		fsi_stream_transfer(&master->fsia.playback);
	if (int_st & AB_IO(1, BO_SHIFT))
		fsi_stream_transfer(&master->fsib.playback);
	if (int_st & AB_IO(1, AI_SHIFT))
		fsi_stream_transfer(&master->fsia.capture);
	if (int_st & AB_IO(1, BI_SHIFT))
		fsi_stream_transfer(&master->fsib.capture);

	fsi_count_fifo_err(&master->fsia);
	fsi_count_fifo_err(&master->fsib);

	fsi_irq_clear_status(&master->fsia);
	fsi_irq_clear_status(&master->fsib);

	return IRQ_HANDLED;
}