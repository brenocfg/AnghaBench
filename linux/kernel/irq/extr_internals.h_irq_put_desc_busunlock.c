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

/* Variables and functions */
 int /*<<< orphan*/  __irq_put_desc_unlock (struct irq_desc*,unsigned long,int) ; 

__attribute__((used)) static inline void
irq_put_desc_busunlock(struct irq_desc *desc, unsigned long flags)
{
	__irq_put_desc_unlock(desc, flags, true);
}