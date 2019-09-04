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
typedef  int /*<<< orphan*/  val32 ;
typedef  scalar_t__ u32 ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_common {scalar_t__ mode; scalar_t__ rts_threshold; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  WSM_MIB_ID_DOT11_RTS_THRESHOLD ; 
 scalar_t__ __cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

int cw1200_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	int ret = 0;
	__le32 val32;
	struct cw1200_common *priv = hw->priv;

	if (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		return 0;

	if (value != (u32) -1)
		val32 = __cpu_to_le32(value);
	else
		val32 = 0; /* disabled */

	if (priv->rts_threshold == value)
		goto out;

	pr_debug("[STA] Setting RTS threshold: %d\n",
		 priv->rts_threshold);

	/* mutex_lock(&priv->conf_mutex); */
	ret = wsm_write_mib(priv, WSM_MIB_ID_DOT11_RTS_THRESHOLD,
			    &val32, sizeof(val32));
	if (!ret)
		priv->rts_threshold = value;
	/* mutex_unlock(&priv->conf_mutex); */

out:
	return ret;
}