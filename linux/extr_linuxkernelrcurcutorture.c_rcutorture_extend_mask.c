#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct torture_random_state {int dummy; } ;
struct TYPE_2__ {int ext_irq_conflict; } ;

/* Variables and functions */
 int RCUTORTURE_RDR_BH ; 
 int RCUTORTURE_RDR_IRQ ; 
 unsigned long RCUTORTURE_RDR_NBITS ; 
 int RCUTORTURE_RDR_RCU ; 
 int RCUTORTURE_RDR_SHIFT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_1__* cur_ops ; 
 int rcutorture_extend_mask_max () ; 
 int torture_random (struct torture_random_state*) ; 

__attribute__((used)) static int
rcutorture_extend_mask(int oldmask, struct torture_random_state *trsp)
{
	int mask = rcutorture_extend_mask_max();
	unsigned long randmask1 = torture_random(trsp) >> 8;
	unsigned long randmask2 = randmask1 >> 1;

	WARN_ON_ONCE(mask >> RCUTORTURE_RDR_SHIFT);
	/* Half the time lots of bits, half the time only one bit. */
	if (randmask1 & 0x1)
		mask = mask & randmask2;
	else
		mask = mask & (1 << (randmask2 % RCUTORTURE_RDR_NBITS));
	if ((mask & RCUTORTURE_RDR_IRQ) &&
	    !(mask & RCUTORTURE_RDR_BH) &&
	    (oldmask & RCUTORTURE_RDR_BH))
		mask |= RCUTORTURE_RDR_BH; /* Can't enable bh w/irq disabled. */
	if ((mask & RCUTORTURE_RDR_IRQ) &&
	    !(mask & cur_ops->ext_irq_conflict) &&
	    (oldmask & cur_ops->ext_irq_conflict))
		mask |= cur_ops->ext_irq_conflict; /* Or if readers object. */
	return mask ?: RCUTORTURE_RDR_RCU;
}