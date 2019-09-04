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
struct vme_lm_resource {int monitors; int /*<<< orphan*/  mtx; TYPE_1__* parent; } ;
struct fake_driver {scalar_t__ lm_enabled; int /*<<< orphan*/ ** lm_callback; int /*<<< orphan*/ ** lm_data; } ;
struct TYPE_2__ {struct fake_driver* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fake_lm_detach(struct vme_lm_resource *lm, int monitor)
{
	u32 tmp;
	int i;
	struct fake_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	/* Detach callback */
	bridge->lm_callback[monitor] = NULL;
	bridge->lm_data[monitor] = NULL;

	/* If all location monitors disabled, disable global Location Monitor */
	tmp = 0;
	for (i = 0; i < lm->monitors; i++) {
		if (bridge->lm_callback[i])
			tmp = 1;
	}

	if (tmp == 0)
		bridge->lm_enabled = 0;

	mutex_unlock(&lm->mtx);

	return 0;
}