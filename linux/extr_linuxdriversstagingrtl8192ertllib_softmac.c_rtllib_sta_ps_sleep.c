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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int tim_count; } ;
struct TYPE_4__ {int dtim_data; int beacon_interval; int dtim_period; scalar_t__ last_dtim_sta_time; TYPE_1__ tim; } ;
struct rt_pwr_save_ctrl {int LPSAwakeIntvl; int RegMaxLPSAwakeIntvl; } ;
struct rtllib_device {int ps; int softmac_features; scalar_t__ mgmt_queue_tail; scalar_t__ mgmt_queue_head; TYPE_2__ current_network; scalar_t__ bAwakePktSent; scalar_t__ last_rx_ps_time; int /*<<< orphan*/  dev; scalar_t__ LPSDelayCnt; struct rt_pwr_save_ctrl PowerSaveControl; } ;

/* Variables and functions */
 int IEEE_SOFTMAC_SINGLE_QUEUE ; 
 int RTLLIB_DTIM_INVALID ; 
 int RTLLIB_DTIM_UCAST ; 
 int RTLLIB_DTIM_VALID ; 
 scalar_t__ dev_trans_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static short rtllib_sta_ps_sleep(struct rtllib_device *ieee, u64 *time)
{
	int timeout;
	u8 dtim;
	struct rt_pwr_save_ctrl *pPSC = &(ieee->PowerSaveControl);

	if (ieee->LPSDelayCnt) {
		ieee->LPSDelayCnt--;
		return 0;
	}

	dtim = ieee->current_network.dtim_data;
	if (!(dtim & RTLLIB_DTIM_VALID))
		return 0;
	timeout = ieee->current_network.beacon_interval;
	ieee->current_network.dtim_data = RTLLIB_DTIM_INVALID;
	/* there's no need to nofity AP that I find you buffered
	 * with broadcast packet
	 */
	if (dtim & (RTLLIB_DTIM_UCAST & ieee->ps))
		return 2;

	if (!time_after(jiffies,
			dev_trans_start(ieee->dev) + msecs_to_jiffies(timeout)))
		return 0;
	if (!time_after(jiffies,
			ieee->last_rx_ps_time + msecs_to_jiffies(timeout)))
		return 0;
	if ((ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE) &&
	    (ieee->mgmt_queue_tail != ieee->mgmt_queue_head))
		return 0;

	if (time) {
		if (ieee->bAwakePktSent) {
			pPSC->LPSAwakeIntvl = 1;
		} else {
			u8 MaxPeriod = 1;

			if (pPSC->LPSAwakeIntvl == 0)
				pPSC->LPSAwakeIntvl = 1;
			if (pPSC->RegMaxLPSAwakeIntvl == 0)
				MaxPeriod = 1;
			else if (pPSC->RegMaxLPSAwakeIntvl == 0xFF)
				MaxPeriod = ieee->current_network.dtim_period;
			else
				MaxPeriod = pPSC->RegMaxLPSAwakeIntvl;
			pPSC->LPSAwakeIntvl = (pPSC->LPSAwakeIntvl >=
					       MaxPeriod) ? MaxPeriod :
					       (pPSC->LPSAwakeIntvl + 1);
		}
		{
			u8 LPSAwakeIntvl_tmp = 0;
			u8 period = ieee->current_network.dtim_period;
			u8 count = ieee->current_network.tim.tim_count;

			if (count == 0) {
				if (pPSC->LPSAwakeIntvl > period)
					LPSAwakeIntvl_tmp = period +
						 (pPSC->LPSAwakeIntvl -
						 period) -
						 ((pPSC->LPSAwakeIntvl-period) %
						 period);
				else
					LPSAwakeIntvl_tmp = pPSC->LPSAwakeIntvl;

			} else {
				if (pPSC->LPSAwakeIntvl >
				    ieee->current_network.tim.tim_count)
					LPSAwakeIntvl_tmp = count +
					(pPSC->LPSAwakeIntvl - count) -
					((pPSC->LPSAwakeIntvl-count)%period);
				else
					LPSAwakeIntvl_tmp = pPSC->LPSAwakeIntvl;
			}

		*time = ieee->current_network.last_dtim_sta_time
			+ msecs_to_jiffies(ieee->current_network.beacon_interval *
			LPSAwakeIntvl_tmp);
	}
	}

	return 1;


}