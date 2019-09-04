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
struct irq_desc {int dummy; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_bad_irq (int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_data_to_desc (struct irq_data*) ; 
 int /*<<< orphan*/  print_irq_desc (int /*<<< orphan*/ ,struct irq_desc*) ; 

__attribute__((used)) static void ack_bad(struct irq_data *data)
{
	struct irq_desc *desc = irq_data_to_desc(data);

	print_irq_desc(data->irq, desc);
	ack_bad_irq(data->irq);
}