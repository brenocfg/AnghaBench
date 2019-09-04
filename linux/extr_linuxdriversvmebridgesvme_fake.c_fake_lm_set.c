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
typedef  int u32 ;
struct vme_lm_resource {int monitors; int /*<<< orphan*/  mtx; struct vme_bridge* parent; } ;
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {unsigned long long lm_base; int lm_aspace; int lm_cycle; scalar_t__* lm_callback; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  VME_A16 131 
#define  VME_A24 130 
#define  VME_A32 129 
#define  VME_A64 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int fake_lm_set(struct vme_lm_resource *lm, unsigned long long lm_base,
		u32 aspace, u32 cycle)
{
	int i;
	struct vme_bridge *fake_bridge;
	struct fake_driver *bridge;

	fake_bridge = lm->parent;

	bridge = fake_bridge->driver_priv;

	mutex_lock(&lm->mtx);

	/* If we already have a callback attached, we can't move it! */
	for (i = 0; i < lm->monitors; i++) {
		if (bridge->lm_callback[i]) {
			mutex_unlock(&lm->mtx);
			pr_err("Location monitor callback attached, can't reset\n");
			return -EBUSY;
		}
	}

	switch (aspace) {
	case VME_A16:
	case VME_A24:
	case VME_A32:
	case VME_A64:
		break;
	default:
		mutex_unlock(&lm->mtx);
		pr_err("Invalid address space\n");
		return -EINVAL;
	}

	bridge->lm_base = lm_base;
	bridge->lm_aspace = aspace;
	bridge->lm_cycle = cycle;

	mutex_unlock(&lm->mtx);

	return 0;
}