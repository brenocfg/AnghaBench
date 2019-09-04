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
struct cw1200_common {int /*<<< orphan*/  bss_loss_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cw1200_cqm_bssloss_sm (struct cw1200_common*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cw1200_cqm_bssloss_sm(struct cw1200_common *priv,
					 int init, int good, int bad)
{
	spin_lock(&priv->bss_loss_lock);
	__cw1200_cqm_bssloss_sm(priv, init, good, bad);
	spin_unlock(&priv->bss_loss_lock);
}