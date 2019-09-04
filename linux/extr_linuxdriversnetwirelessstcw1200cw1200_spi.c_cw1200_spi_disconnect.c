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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct hwbus_priv {int /*<<< orphan*/ * core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_core_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_spi_irq_unsubscribe (struct hwbus_priv*) ; 
 int /*<<< orphan*/  cw1200_spi_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct hwbus_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int cw1200_spi_disconnect(struct spi_device *func)
{
	struct hwbus_priv *self = spi_get_drvdata(func);

	if (self) {
		cw1200_spi_irq_unsubscribe(self);
		if (self->core) {
			cw1200_core_release(self->core);
			self->core = NULL;
		}
	}
	cw1200_spi_off(dev_get_platdata(&func->dev));

	return 0;
}