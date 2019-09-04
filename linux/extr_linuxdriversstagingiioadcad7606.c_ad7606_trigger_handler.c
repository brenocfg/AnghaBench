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
struct iio_poll_func {int /*<<< orphan*/  indio_dev; } ;
struct ad7606_state {int /*<<< orphan*/  gpio_convst; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad7606_state* iio_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad7606_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct ad7606_state *st = iio_priv(pf->indio_dev);

	gpiod_set_value(st->gpio_convst, 1);

	return IRQ_HANDLED;
}