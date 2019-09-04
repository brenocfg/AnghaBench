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
struct sta_info {int /*<<< orphan*/  mac_id; } ;
struct hal_com_data {int /*<<< orphan*/  odmpriv; } ;
struct adapter {int dummy; } ;
typedef  enum HAL_ODM_VARIABLE { ____Placeholder_HAL_ODM_VARIABLE } HAL_ODM_VARIABLE ;
typedef  int /*<<< orphan*/ * PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,int /*<<< orphan*/ ) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
#define  HAL_ODM_P2P_STATE 130 
#define  HAL_ODM_STA_INFO 129 
#define  HAL_ODM_WIFI_DISPLAY_STATE 128 
 int /*<<< orphan*/  ODM_CMNINFO_STA_STATUS ; 
 int /*<<< orphan*/  ODM_CMNINFO_WIFI_DIRECT ; 
 int /*<<< orphan*/  ODM_CMNINFO_WIFI_DISPLAY ; 
 int /*<<< orphan*/  ODM_CmnInfoPtrArrayHook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  ODM_CmnInfoUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void SetHalODMVar(
	struct adapter *Adapter,
	enum HAL_ODM_VARIABLE eVariable,
	void *pValue1,
	bool bSet
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	PDM_ODM_T podmpriv = &pHalData->odmpriv;
	/* _irqL irqL; */
	switch (eVariable) {
	case HAL_ODM_STA_INFO:
		{
			struct sta_info *psta = pValue1;
			if (bSet) {
				DBG_8192C("### Set STA_(%d) info ###\n", psta->mac_id);
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, psta);
			} else {
				DBG_8192C("### Clean STA_(%d) info ###\n", psta->mac_id);
				/* spin_lock_bh(&pHalData->odm_stainfo_lock); */
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, NULL);

				/* spin_unlock_bh(&pHalData->odm_stainfo_lock); */
		    }
		}
		break;
	case HAL_ODM_P2P_STATE:
			ODM_CmnInfoUpdate(podmpriv, ODM_CMNINFO_WIFI_DIRECT, bSet);
		break;
	case HAL_ODM_WIFI_DISPLAY_STATE:
			ODM_CmnInfoUpdate(podmpriv, ODM_CMNINFO_WIFI_DISPLAY, bSet);
		break;
	#if defined(CONFIG_SIGNAL_DISPLAY_DBM) && defined(CONFIG_BACKGROUND_NOISE_MONITOR)
	case HAL_ODM_NOISE_MONITOR:
		{
			struct noise_info *pinfo = pValue1;

			#ifdef DBG_NOISE_MONITOR
			DBG_8192C("### Noise monitor chan(%d)-bPauseDIG:%d, IGIValue:0x%02x, max_time:%d (ms) ###\n",
				pinfo->chan, pinfo->bPauseDIG, pinfo->IGIValue, pinfo->max_time);
			#endif

			pHalData->noise[pinfo->chan] = ODM_InbandNoise_Monitor(podmpriv, pinfo->bPauseDIG, pinfo->IGIValue, pinfo->max_time);
			DBG_871X("chan_%d, noise = %d (dBm)\n", pinfo->chan, pHalData->noise[pinfo->chan]);
			#ifdef DBG_NOISE_MONITOR
			DBG_871X("noise_a = %d, noise_b = %d  noise_all:%d\n",
				podmpriv->noise_level.noise[ODM_RF_PATH_A],
				podmpriv->noise_level.noise[ODM_RF_PATH_B],
				podmpriv->noise_level.noise_all);
			#endif
		}
		break;
	#endif/* ifdef CONFIG_BACKGROUND_NOISE_MONITOR */

	default:
		break;
	}
}