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
struct spi_message {int status; int /*<<< orphan*/ * context; struct spi_device* spi; int /*<<< orphan*/  complete; } ;
struct spi_device {int /*<<< orphan*/  statistics; struct spi_controller* controller; } ;
struct spi_controller {scalar_t__ transfer; int /*<<< orphan*/  statistics; int /*<<< orphan*/  bus_lock_spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_STATISTICS_INCREMENT_FIELD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __spi_pump_messages (struct spi_controller*,int) ; 
 int __spi_queued_transfer (struct spi_device*,struct spi_message*,int) ; 
 int __spi_validate (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  done ; 
 int spi_async_locked (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_complete ; 
 scalar_t__ spi_queued_transfer ; 
 int /*<<< orphan*/  spi_sync ; 
 int /*<<< orphan*/  spi_sync_immediate ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_spi_message_submit (struct spi_message*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __spi_sync(struct spi_device *spi, struct spi_message *message)
{
	DECLARE_COMPLETION_ONSTACK(done);
	int status;
	struct spi_controller *ctlr = spi->controller;
	unsigned long flags;

	status = __spi_validate(spi, message);
	if (status != 0)
		return status;

	message->complete = spi_complete;
	message->context = &done;
	message->spi = spi;

	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics, spi_sync);
	SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics, spi_sync);

	/* If we're not using the legacy transfer method then we will
	 * try to transfer in the calling context so special case.
	 * This code would be less tricky if we could remove the
	 * support for driver implemented message queues.
	 */
	if (ctlr->transfer == spi_queued_transfer) {
		spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

		trace_spi_message_submit(message);

		status = __spi_queued_transfer(spi, message, false);

		spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);
	} else {
		status = spi_async_locked(spi, message);
	}

	if (status == 0) {
		/* Push out the messages in the calling context if we
		 * can.
		 */
		if (ctlr->transfer == spi_queued_transfer) {
			SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics,
						       spi_sync_immediate);
			SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics,
						       spi_sync_immediate);
			__spi_pump_messages(ctlr, false);
		}

		wait_for_completion(&done);
		status = message->status;
	}
	message->context = NULL;
	return status;
}