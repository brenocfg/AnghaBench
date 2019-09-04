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
struct sclp_register {int receive_mask; int send_mask; int /*<<< orphan*/  list; scalar_t__ pm_event_posted; scalar_t__ sclp_send_mask; scalar_t__ sclp_receive_mask; } ;
typedef  int sccb_mask_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __sclp_get_mask (int*,int*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int sclp_init () ; 
 int sclp_init_mask (int) ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_reg_list ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
sclp_register(struct sclp_register *reg)
{
	unsigned long flags;
	sccb_mask_t receive_mask;
	sccb_mask_t send_mask;
	int rc;

	rc = sclp_init();
	if (rc)
		return rc;
	spin_lock_irqsave(&sclp_lock, flags);
	/* Check event mask for collisions */
	__sclp_get_mask(&receive_mask, &send_mask);
	if (reg->receive_mask & receive_mask || reg->send_mask & send_mask) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return -EBUSY;
	}
	/* Trigger initial state change callback */
	reg->sclp_receive_mask = 0;
	reg->sclp_send_mask = 0;
	reg->pm_event_posted = 0;
	list_add(&reg->list, &sclp_reg_list);
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_init_mask(1);
	if (rc) {
		spin_lock_irqsave(&sclp_lock, flags);
		list_del(&reg->list);
		spin_unlock_irqrestore(&sclp_lock, flags);
	}
	return rc;
}