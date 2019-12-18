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
struct irq_bypass_producer {int /*<<< orphan*/  (* start ) (struct irq_bypass_producer*) ;int /*<<< orphan*/  (* del_consumer ) (struct irq_bypass_producer*,struct irq_bypass_consumer*) ;int /*<<< orphan*/  (* stop ) (struct irq_bypass_producer*) ;} ;
struct irq_bypass_consumer {int /*<<< orphan*/  (* start ) (struct irq_bypass_consumer*) ;int /*<<< orphan*/  (* del_producer ) (struct irq_bypass_consumer*,struct irq_bypass_producer*) ;int /*<<< orphan*/  (* stop ) (struct irq_bypass_consumer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct irq_bypass_producer*) ; 
 int /*<<< orphan*/  stub2 (struct irq_bypass_consumer*) ; 
 int /*<<< orphan*/  stub3 (struct irq_bypass_consumer*,struct irq_bypass_producer*) ; 
 int /*<<< orphan*/  stub4 (struct irq_bypass_producer*,struct irq_bypass_consumer*) ; 
 int /*<<< orphan*/  stub5 (struct irq_bypass_consumer*) ; 
 int /*<<< orphan*/  stub6 (struct irq_bypass_producer*) ; 

__attribute__((used)) static void __disconnect(struct irq_bypass_producer *prod,
			 struct irq_bypass_consumer *cons)
{
	if (prod->stop)
		prod->stop(prod);
	if (cons->stop)
		cons->stop(cons);

	cons->del_producer(cons, prod);

	if (prod->del_consumer)
		prod->del_consumer(prod, cons);

	if (cons->start)
		cons->start(cons);
	if (prod->start)
		prod->start(prod);
}