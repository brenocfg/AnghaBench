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
struct iio_dev {int dummy; } ;
struct ad7606_state {int done; int /*<<< orphan*/  wq_data_avail; int /*<<< orphan*/  poll_work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ad7606_interrupt(int irq, void *dev_id)
{
	struct iio_dev *indio_dev = dev_id;
	struct ad7606_state *st = iio_priv(indio_dev);

	if (iio_buffer_enabled(indio_dev)) {
		schedule_work(&st->poll_work);
	} else {
		st->done = true;
		wake_up_interruptible(&st->wq_data_avail);
	}

	return IRQ_HANDLED;
}