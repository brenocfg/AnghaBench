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
typedef  size_t u8 ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_1__* stations; } ;
struct il_link_quality_cmd {int dummy; } ;
struct TYPE_2__ {struct il_link_quality_cmd* lq; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 size_t IL_INVALID_STATION ; 
 int /*<<< orphan*/  IL_STA_BCAST ; 
 int /*<<< orphan*/  IL_STA_DRIVER_ACTIVE ; 
 struct il_link_quality_cmd* il4965_sta_alloc_lq (struct il_priv*,size_t) ; 
 int /*<<< orphan*/  il_bcast_addr ; 
 size_t il_prep_station (struct il_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il4965_alloc_bcast_station(struct il_priv *il)
{
	struct il_link_quality_cmd *link_cmd;
	unsigned long flags;
	u8 sta_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	sta_id = il_prep_station(il, il_bcast_addr, false, NULL);
	if (sta_id == IL_INVALID_STATION) {
		IL_ERR("Unable to prepare broadcast station\n");
		spin_unlock_irqrestore(&il->sta_lock, flags);

		return -EINVAL;
	}

	il->stations[sta_id].used |= IL_STA_DRIVER_ACTIVE;
	il->stations[sta_id].used |= IL_STA_BCAST;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	link_cmd = il4965_sta_alloc_lq(il, sta_id);
	if (!link_cmd) {
		IL_ERR
		    ("Unable to initialize rate scaling for bcast station.\n");
		return -ENOMEM;
	}

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].lq = link_cmd;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	return 0;
}