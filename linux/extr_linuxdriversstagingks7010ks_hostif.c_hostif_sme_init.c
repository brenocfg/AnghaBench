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
struct TYPE_2__ {scalar_t__ sme_flag; int /*<<< orphan*/  sme_spin; scalar_t__ qtail; scalar_t__ qhead; int /*<<< orphan*/  sme_status; } ;
struct ks_wlan_private {int /*<<< orphan*/  sme_task; TYPE_1__ sme_i; } ;

/* Variables and functions */
 int /*<<< orphan*/  SME_IDLE ; 
 int /*<<< orphan*/  hostif_sme_task ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void hostif_sme_init(struct ks_wlan_private *priv)
{
	priv->sme_i.sme_status = SME_IDLE;
	priv->sme_i.qhead = 0;
	priv->sme_i.qtail = 0;
	spin_lock_init(&priv->sme_i.sme_spin);
	priv->sme_i.sme_flag = 0;
	tasklet_init(&priv->sme_task, hostif_sme_task, (unsigned long)priv);
}