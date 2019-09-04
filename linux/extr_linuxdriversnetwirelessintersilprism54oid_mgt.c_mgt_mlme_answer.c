#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ iw_mode; int /*<<< orphan*/  mib_sem; scalar_t__* mib; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 scalar_t__ DOT11_MLME_INTERMEDIATE ; 
 size_t DOT11_OID_MLMEAUTOLEVEL ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int
mgt_mlme_answer(islpci_private *priv)
{
	u32 mlmeautolevel;
	/* Acquire a read lock because if we are in a mode change, it's
	 * possible to answer true, while the card is leaving master to managed
	 * mode. Answering to a mlme in this situation could hang the card.
	 */
	down_read(&priv->mib_sem);
	mlmeautolevel =
	    le32_to_cpu(*(u32 *) priv->mib[DOT11_OID_MLMEAUTOLEVEL]);
	up_read(&priv->mib_sem);

	return ((priv->iw_mode == IW_MODE_MASTER) &&
		(mlmeautolevel >= DOT11_MLME_INTERMEDIATE));
}