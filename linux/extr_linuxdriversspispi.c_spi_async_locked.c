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
struct spi_message {int dummy; } ;
struct spi_device {struct spi_controller* controller; } ;
struct spi_controller {int /*<<< orphan*/  bus_lock_spinlock; } ;

/* Variables and functions */
 int __spi_async (struct spi_device*,struct spi_message*) ; 
 int __spi_validate (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int spi_async_locked(struct spi_device *spi, struct spi_message *message)
{
	struct spi_controller *ctlr = spi->controller;
	int ret;
	unsigned long flags;

	ret = __spi_validate(spi, message);
	if (ret != 0)
		return ret;

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

	ret = __spi_async(spi, message);

	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	return ret;

}