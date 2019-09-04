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
typedef  int u32 ;
struct vme_lm_resource {int /*<<< orphan*/  mtx; TYPE_1__* parent; } ;
struct ca91cx42_driver {scalar_t__ base; } ;
struct TYPE_2__ {struct ca91cx42_driver* driver_priv; } ;

/* Variables and functions */
 int CA91CX42_LM_CTL_AS_A16 ; 
 int CA91CX42_LM_CTL_AS_A24 ; 
 int CA91CX42_LM_CTL_AS_A32 ; 
 int CA91CX42_LM_CTL_AS_M ; 
 int CA91CX42_LM_CTL_DATA ; 
 int CA91CX42_LM_CTL_EN ; 
 int CA91CX42_LM_CTL_NPRIV ; 
 int CA91CX42_LM_CTL_PGM ; 
 int CA91CX42_LM_CTL_SUPR ; 
 scalar_t__ LM_BS ; 
 scalar_t__ LM_CTL ; 
 int VME_A16 ; 
 int VME_A24 ; 
 int VME_A32 ; 
 int VME_DATA ; 
 int VME_PROG ; 
 int VME_SUPER ; 
 int VME_USER ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ca91cx42_lm_get(struct vme_lm_resource *lm,
	unsigned long long *lm_base, u32 *aspace, u32 *cycle)
{
	u32 lm_ctl, enabled = 0;
	struct ca91cx42_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	*lm_base = (unsigned long long)ioread32(bridge->base + LM_BS);
	lm_ctl = ioread32(bridge->base + LM_CTL);

	if (lm_ctl & CA91CX42_LM_CTL_EN)
		enabled = 1;

	if ((lm_ctl & CA91CX42_LM_CTL_AS_M) == CA91CX42_LM_CTL_AS_A16)
		*aspace = VME_A16;
	if ((lm_ctl & CA91CX42_LM_CTL_AS_M) == CA91CX42_LM_CTL_AS_A24)
		*aspace = VME_A24;
	if ((lm_ctl & CA91CX42_LM_CTL_AS_M) == CA91CX42_LM_CTL_AS_A32)
		*aspace = VME_A32;

	*cycle = 0;
	if (lm_ctl & CA91CX42_LM_CTL_SUPR)
		*cycle |= VME_SUPER;
	if (lm_ctl & CA91CX42_LM_CTL_NPRIV)
		*cycle |= VME_USER;
	if (lm_ctl & CA91CX42_LM_CTL_PGM)
		*cycle |= VME_PROG;
	if (lm_ctl & CA91CX42_LM_CTL_DATA)
		*cycle |= VME_DATA;

	mutex_unlock(&lm->mtx);

	return enabled;
}