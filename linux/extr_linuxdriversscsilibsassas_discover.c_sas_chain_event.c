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
struct sas_work {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  sas_chain_work (struct sas_ha_struct*,struct sas_work*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int,unsigned long*) ; 

__attribute__((used)) static void sas_chain_event(int event, unsigned long *pending,
			    struct sas_work *sw,
			    struct sas_ha_struct *ha)
{
	if (!test_and_set_bit(event, pending)) {
		unsigned long flags;

		spin_lock_irqsave(&ha->lock, flags);
		sas_chain_work(ha, sw);
		spin_unlock_irqrestore(&ha->lock, flags);
	}
}