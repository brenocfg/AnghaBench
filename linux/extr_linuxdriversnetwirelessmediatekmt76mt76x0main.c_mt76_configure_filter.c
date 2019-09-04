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
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
struct mt76x0_dev {int rxfilter; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;

/* Variables and functions */
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_PLCPFAIL ; 
 unsigned int FIF_PSPOLL ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int MT_RX_FILTR_CFG_ACK ; 
 int MT_RX_FILTR_CFG_BA ; 
 int MT_RX_FILTR_CFG_CFACK ; 
 int MT_RX_FILTR_CFG_CFEND ; 
 int MT_RX_FILTR_CFG_CRC_ERR ; 
 int MT_RX_FILTR_CFG_CTRL_RSV ; 
 int MT_RX_FILTR_CFG_CTS ; 
 int MT_RX_FILTR_CFG_OTHER_BSS ; 
 int MT_RX_FILTR_CFG_PHY_ERR ; 
 int MT_RX_FILTR_CFG_PSPOLL ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76_configure_filter(struct ieee80211_hw *hw, unsigned int changed_flags,
		      unsigned int *total_flags, u64 multicast)
{
	struct mt76x0_dev *dev = hw->priv;
	u32 flags = 0;

#define MT76_FILTER(_flag, _hw) do { \
		flags |= *total_flags & FIF_##_flag;			\
		dev->rxfilter &= ~(_hw);				\
		dev->rxfilter |= !(flags & FIF_##_flag) * (_hw);	\
	} while (0)

	mutex_lock(&dev->mutex);

	dev->rxfilter &= ~MT_RX_FILTR_CFG_OTHER_BSS;

	MT76_FILTER(FCSFAIL, MT_RX_FILTR_CFG_CRC_ERR);
	MT76_FILTER(PLCPFAIL, MT_RX_FILTR_CFG_PHY_ERR);
	MT76_FILTER(CONTROL, MT_RX_FILTR_CFG_ACK |
			     MT_RX_FILTR_CFG_CTS |
			     MT_RX_FILTR_CFG_CFEND |
			     MT_RX_FILTR_CFG_CFACK |
			     MT_RX_FILTR_CFG_BA |
			     MT_RX_FILTR_CFG_CTRL_RSV);
	MT76_FILTER(PSPOLL, MT_RX_FILTR_CFG_PSPOLL);

	*total_flags = flags;
	mt76_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);

	mutex_unlock(&dev->mutex);
}