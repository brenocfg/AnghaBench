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
struct hpios_spinlock {int /*<<< orphan*/  lock_context; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_LOCK_BH ; 
 int /*<<< orphan*/  IN_LOCK_IRQ ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cond_lock(struct hpios_spinlock *l)
{
	if (irqs_disabled()) {
		/* NO bh or isr can execute on this processor,
		   so ordinary lock will do
		 */
		spin_lock(&((l)->lock));
		l->lock_context = IN_LOCK_IRQ;
	} else {
		spin_lock_bh(&((l)->lock));
		l->lock_context = IN_LOCK_BH;
	}
}