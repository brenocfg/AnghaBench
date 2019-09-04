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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EVENT_CODE_AD7816_OTI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (void*) ; 
 int /*<<< orphan*/  iio_push_event (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad7816_event_handler(int irq, void *private)
{
	iio_push_event(private, IIO_EVENT_CODE_AD7816_OTI,
		       iio_get_time_ns(private));
	return IRQ_HANDLED;
}