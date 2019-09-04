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
struct TYPE_2__ {int dwevent; int bystate; } ;
union atto_vda_ae {TYPE_1__ lu; } ;
typedef  int u32 ;
typedef  int u16 ;
struct esas2r_target {scalar_t__ new_target_state; int /*<<< orphan*/  lu_event; } ;
struct esas2r_adapter {int /*<<< orphan*/  mem_lock; struct esas2r_target* targetdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCDE_DEV_CHANGE ; 
 scalar_t__ TS_INVALID ; 
 void* TS_NOT_PRESENT ; 
 scalar_t__ TS_PRESENT ; 
#define  VDAAE_LU_DEGRADED 133 
#define  VDAAE_LU_DELETED 132 
#define  VDAAE_LU_FACTORY_DISABLED 131 
 int VDAAE_LU_LOST ; 
#define  VDAAE_LU_NOT_PRESENT 130 
#define  VDAAE_LU_OFFLINE 129 
#define  VDAAE_LU_ONLINE 128 
 int /*<<< orphan*/  esas2r_disc_queue_event (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void esas2r_lun_event(struct esas2r_adapter *a, union atto_vda_ae *ae,
			     u16 target, u32 length)
{
	struct esas2r_target *t = a->targetdb + target;
	u32 cplen = length;
	unsigned long flags;

	if (cplen > sizeof(t->lu_event))
		cplen = sizeof(t->lu_event);

	esas2r_trace("ae->lu.dwevent: %x", ae->lu.dwevent);
	esas2r_trace("ae->lu.bystate: %x", ae->lu.bystate);

	spin_lock_irqsave(&a->mem_lock, flags);

	t->new_target_state = TS_INVALID;

	if (ae->lu.dwevent  & VDAAE_LU_LOST) {
		t->new_target_state = TS_NOT_PRESENT;
	} else {
		switch (ae->lu.bystate) {
		case VDAAE_LU_NOT_PRESENT:
		case VDAAE_LU_OFFLINE:
		case VDAAE_LU_DELETED:
		case VDAAE_LU_FACTORY_DISABLED:
			t->new_target_state = TS_NOT_PRESENT;
			break;

		case VDAAE_LU_ONLINE:
		case VDAAE_LU_DEGRADED:
			t->new_target_state = TS_PRESENT;
			break;
		}
	}

	if (t->new_target_state != TS_INVALID) {
		memcpy(&t->lu_event, &ae->lu, cplen);

		esas2r_disc_queue_event(a, DCDE_DEV_CHANGE);
	}

	spin_unlock_irqrestore(&a->mem_lock, flags);
}