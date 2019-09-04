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
typedef  size_t u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int /*<<< orphan*/  uapsd; int /*<<< orphan*/  txop; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  aifs; } ;
struct ieee80211_hw {size_t queues; struct cw1200_common* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  uapsd_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ * params; } ;
struct cw1200_common {scalar_t__ mode; scalar_t__ join_status; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  powersave_mode; TYPE_1__ uapsd_info; scalar_t__ setbssparams_done; int /*<<< orphan*/  edca; TYPE_2__ tx_queue_params; } ;

/* Variables and functions */
 scalar_t__ CW1200_JOIN_STATUS_STA ; 
 int EINVAL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WSM_EDCA_SET (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_TX_QUEUE_SET (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cw1200_set_pm (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int cw1200_set_uapsd_param (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wsm_set_edca_params (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int wsm_set_tx_queue_params (struct cw1200_common*,int /*<<< orphan*/ *,size_t) ; 

int cw1200_conf_tx(struct ieee80211_hw *dev, struct ieee80211_vif *vif,
		   u16 queue, const struct ieee80211_tx_queue_params *params)
{
	struct cw1200_common *priv = dev->priv;
	int ret = 0;
	/* To prevent re-applying PM request OID again and again*/
	bool old_uapsd_flags;

	mutex_lock(&priv->conf_mutex);

	if (queue < dev->queues) {
		old_uapsd_flags = le16_to_cpu(priv->uapsd_info.uapsd_flags);

		WSM_TX_QUEUE_SET(&priv->tx_queue_params, queue, 0, 0, 0);
		ret = wsm_set_tx_queue_params(priv,
					      &priv->tx_queue_params.params[queue], queue);
		if (ret) {
			ret = -EINVAL;
			goto out;
		}

		WSM_EDCA_SET(&priv->edca, queue, params->aifs,
			     params->cw_min, params->cw_max,
			     params->txop, 0xc8,
			     params->uapsd);
		ret = wsm_set_edca_params(priv, &priv->edca);
		if (ret) {
			ret = -EINVAL;
			goto out;
		}

		if (priv->mode == NL80211_IFTYPE_STATION) {
			ret = cw1200_set_uapsd_param(priv, &priv->edca);
			if (!ret && priv->setbssparams_done &&
			    (priv->join_status == CW1200_JOIN_STATUS_STA) &&
			    (old_uapsd_flags != le16_to_cpu(priv->uapsd_info.uapsd_flags)))
				ret = cw1200_set_pm(priv, &priv->powersave_mode);
		}
	} else {
		ret = -EINVAL;
	}

out:
	mutex_unlock(&priv->conf_mutex);
	return ret;
}