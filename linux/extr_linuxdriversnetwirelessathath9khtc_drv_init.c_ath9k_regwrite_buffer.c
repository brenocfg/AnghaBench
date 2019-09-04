#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {TYPE_2__* wmi; } ;
struct TYPE_4__ {size_t multi_write_idx; int /*<<< orphan*/  multi_write_mutex; TYPE_1__* multi_write; } ;
struct TYPE_3__ {void* val; void* reg; } ;

/* Variables and functions */
 size_t MAX_CMD_NUMBER ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_regwrite_multi (struct ath_common*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_regwrite_buffer(void *hw_priv, u32 val, u32 reg_offset)
{
	struct ath_hw *ah = hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;

	mutex_lock(&priv->wmi->multi_write_mutex);

	/* Store the register/value */
	priv->wmi->multi_write[priv->wmi->multi_write_idx].reg =
		cpu_to_be32(reg_offset);
	priv->wmi->multi_write[priv->wmi->multi_write_idx].val =
		cpu_to_be32(val);

	priv->wmi->multi_write_idx++;

	/* If the buffer is full, send it out. */
	if (priv->wmi->multi_write_idx == MAX_CMD_NUMBER)
		ath9k_regwrite_multi(common);

	mutex_unlock(&priv->wmi->multi_write_mutex);
}