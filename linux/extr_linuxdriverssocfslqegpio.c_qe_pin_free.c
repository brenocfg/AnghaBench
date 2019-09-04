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
struct qe_pin {int num; struct qe_gpio_chip* controller; } ;
struct qe_gpio_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pin_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QE_PIN_REQUESTED ; 
 int /*<<< orphan*/  kfree (struct qe_pin*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qe_pin_free(struct qe_pin *qe_pin)
{
	struct qe_gpio_chip *qe_gc = qe_pin->controller;
	unsigned long flags;
	const int pin = qe_pin->num;

	spin_lock_irqsave(&qe_gc->lock, flags);
	test_and_clear_bit(QE_PIN_REQUESTED, &qe_gc->pin_flags[pin]);
	spin_unlock_irqrestore(&qe_gc->lock, flags);

	kfree(qe_pin);
}