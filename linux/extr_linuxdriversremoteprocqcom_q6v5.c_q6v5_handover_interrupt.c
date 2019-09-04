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
struct qcom_q6v5 {int handover_issued; int /*<<< orphan*/  (* handover ) (struct qcom_q6v5*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stub1 (struct qcom_q6v5*) ; 

__attribute__((used)) static irqreturn_t q6v5_handover_interrupt(int irq, void *data)
{
	struct qcom_q6v5 *q6v5 = data;

	if (q6v5->handover)
		q6v5->handover(q6v5);

	q6v5->handover_issued = true;

	return IRQ_HANDLED;
}