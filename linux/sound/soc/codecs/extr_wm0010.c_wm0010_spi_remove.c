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
struct wm0010_priv {scalar_t__ irq; int /*<<< orphan*/  gpio_reset_value; int /*<<< orphan*/  gpio_reset; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct wm0010_priv*) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irq_wake (scalar_t__,int /*<<< orphan*/ ) ; 
 struct wm0010_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int wm0010_spi_remove(struct spi_device *spi)
{
	struct wm0010_priv *wm0010 = spi_get_drvdata(spi);

	gpio_set_value_cansleep(wm0010->gpio_reset,
				wm0010->gpio_reset_value);

	irq_set_irq_wake(wm0010->irq, 0);

	if (wm0010->irq)
		free_irq(wm0010->irq, wm0010);

	return 0;
}