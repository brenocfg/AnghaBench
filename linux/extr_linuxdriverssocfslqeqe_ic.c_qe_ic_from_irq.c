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
struct qe_ic {int dummy; } ;

/* Variables and functions */
 struct qe_ic* irq_get_chip_data (unsigned int) ; 

__attribute__((used)) static inline struct qe_ic *qe_ic_from_irq(unsigned int virq)
{
	return irq_get_chip_data(virq);
}