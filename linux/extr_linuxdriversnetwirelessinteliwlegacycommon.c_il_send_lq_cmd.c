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
typedef  int u8 ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_1__* stations; } ;
struct il_link_quality_cmd {size_t sta_id; } ;
struct il_host_cmd {int len; int flags; struct il_link_quality_cmd* data; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CMD_ASYNC ; 
 int /*<<< orphan*/  C_TX_LINK_QUALITY_CMD ; 
 int /*<<< orphan*/  D_INFO (char*,size_t) ; 
 int EINVAL ; 
 size_t IL_INVALID_STATION ; 
 int IL_STA_DRIVER_ACTIVE ; 
 int IL_STA_UCODE_INPROGRESS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  il_dump_lq_cmd (struct il_priv*,struct il_link_quality_cmd*) ; 
 scalar_t__ il_is_lq_table_valid (struct il_priv*,struct il_link_quality_cmd*) ; 
 int il_send_cmd (struct il_priv*,struct il_host_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il_send_lq_cmd(struct il_priv *il, struct il_link_quality_cmd *lq,
	       u8 flags, bool init)
{
	int ret = 0;
	unsigned long flags_spin;

	struct il_host_cmd cmd = {
		.id = C_TX_LINK_QUALITY_CMD,
		.len = sizeof(struct il_link_quality_cmd),
		.flags = flags,
		.data = lq,
	};

	if (WARN_ON(lq->sta_id == IL_INVALID_STATION))
		return -EINVAL;

	spin_lock_irqsave(&il->sta_lock, flags_spin);
	if (!(il->stations[lq->sta_id].used & IL_STA_DRIVER_ACTIVE)) {
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
		return -EINVAL;
	}
	spin_unlock_irqrestore(&il->sta_lock, flags_spin);

	il_dump_lq_cmd(il, lq);
	BUG_ON(init && (cmd.flags & CMD_ASYNC));

	if (il_is_lq_table_valid(il, lq))
		ret = il_send_cmd(il, &cmd);
	else
		ret = -EINVAL;

	if (cmd.flags & CMD_ASYNC)
		return ret;

	if (init) {
		D_INFO("init LQ command complete,"
		       " clearing sta addition status for sta %d\n",
		       lq->sta_id);
		spin_lock_irqsave(&il->sta_lock, flags_spin);
		il->stations[lq->sta_id].used &= ~IL_STA_UCODE_INPROGRESS;
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
	}
	return ret;
}