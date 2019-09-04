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
struct vme_bridge {int /*<<< orphan*/  parent; struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {scalar_t__ base; scalar_t__* lm_callback; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ TSI148_LCSR_LMAT ; 
 int TSI148_LCSR_LMAT_AS_A16 ; 
 int TSI148_LCSR_LMAT_AS_A24 ; 
 int TSI148_LCSR_LMAT_AS_A32 ; 
 int TSI148_LCSR_LMAT_AS_A64 ; 
 int TSI148_LCSR_LMAT_DATA ; 
 int TSI148_LCSR_LMAT_NPRIV ; 
 int TSI148_LCSR_LMAT_PGM ; 
 int TSI148_LCSR_LMAT_SUPR ; 
 scalar_t__ TSI148_LCSR_LMBAL ; 
 scalar_t__ TSI148_LCSR_LMBAU ; 
#define  VME_A16 131 
#define  VME_A24 130 
#define  VME_A32 129 
#define  VME_A64 128 
 int VME_DATA ; 
 int VME_PROG ; 
 int VME_SUPER ; 
 int VME_USER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_split (unsigned long long,int*,int*) ; 

__attribute__((used)) static int tsi148_lm_set(struct vme_lm_resource *lm, unsigned long long lm_base,
	u32 aspace, u32 cycle)
{
	u32 lm_base_high, lm_base_low, lm_ctl = 0;
	int i;
	struct vme_bridge *tsi148_bridge;
	struct tsi148_driver *bridge;

	tsi148_bridge = lm->parent;

	bridge = tsi148_bridge->driver_priv;

	mutex_lock(&lm->mtx);

	/* If we already have a callback attached, we can't move it! */
	for (i = 0; i < lm->monitors; i++) {
		if (bridge->lm_callback[i]) {
			mutex_unlock(&lm->mtx);
			dev_err(tsi148_bridge->parent, "Location monitor "
				"callback attached, can't reset\n");
			return -EBUSY;
		}
	}

	switch (aspace) {
	case VME_A16:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A16;
		break;
	case VME_A24:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A24;
		break;
	case VME_A32:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A32;
		break;
	case VME_A64:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A64;
		break;
	default:
		mutex_unlock(&lm->mtx);
		dev_err(tsi148_bridge->parent, "Invalid address space\n");
		return -EINVAL;
		break;
	}

	if (cycle & VME_SUPER)
		lm_ctl |= TSI148_LCSR_LMAT_SUPR ;
	if (cycle & VME_USER)
		lm_ctl |= TSI148_LCSR_LMAT_NPRIV;
	if (cycle & VME_PROG)
		lm_ctl |= TSI148_LCSR_LMAT_PGM;
	if (cycle & VME_DATA)
		lm_ctl |= TSI148_LCSR_LMAT_DATA;

	reg_split(lm_base, &lm_base_high, &lm_base_low);

	iowrite32be(lm_base_high, bridge->base + TSI148_LCSR_LMBAU);
	iowrite32be(lm_base_low, bridge->base + TSI148_LCSR_LMBAL);
	iowrite32be(lm_ctl, bridge->base + TSI148_LCSR_LMAT);

	mutex_unlock(&lm->mtx);

	return 0;
}