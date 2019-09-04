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
typedef  int u8 ;
struct hal_com_data {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
#define  HW_VAR_DM_IN_LPS 131 
#define  HW_VAR_RXDMA_AGG_PG_TH 130 
#define  HW_VAR_SET_REQ_FW_PS 129 
#define  HW_VAR_SET_RPWM 128 
 int SDIO_LOCAL_BASE ; 
 int SDIO_REG_HRPWM1 ; 
 int /*<<< orphan*/  SetHwReg8723B (struct adapter*,int,int*) ; 
 int /*<<< orphan*/  rtl8723b_hal_dm_in_lps (struct adapter*) ; 
 int rtw_read8 (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int,int) ; 

__attribute__((used)) static void SetHwReg8723BS(struct adapter *padapter, u8 variable, u8 *val)
{
	struct hal_com_data *pHalData;
	u8 val8;

#if defined(CONFIG_WOWLAN) || defined(CONFIG_AP_WOWLAN)
	struct wowlan_ioctl_param *poidparam;
	struct pwrctrl_priv *pwrctl = adapter_to_pwrctl(padapter);
	int res;
	u32 tmp;
	u16 len = 0;
	u8 trycnt = 100;
	u32 himr = 0;
#if defined(CONFIG_WOWLAN)
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct sta_info *psta = NULL;
	u64 iv_low = 0, iv_high = 0;
	u8 mstatus = (*(u8 *)val);
#endif
#endif

	pHalData = GET_HAL_DATA(padapter);

	switch (variable) {
	case HW_VAR_SET_RPWM:
		/*  rpwm value only use BIT0(clock bit) , BIT6(Ack bit), and BIT7(Toggle bit) */
		/*  BIT0 value - 1: 32k, 0:40MHz. */
		/*  BIT6 value - 1: report cpwm value after success set, 0:do not report. */
		/*  BIT7 value - Toggle bit change. */
		{
			val8 = *val;
			val8 &= 0xC1;
			rtw_write8(padapter, SDIO_LOCAL_BASE|SDIO_REG_HRPWM1, val8);
		}
		break;
	case HW_VAR_SET_REQ_FW_PS:
		{
			u8 req_fw_ps = 0;
			req_fw_ps = rtw_read8(padapter, 0x8f);
			req_fw_ps |= 0x10;
			rtw_write8(padapter, 0x8f, req_fw_ps);
		}
		break;
	case HW_VAR_RXDMA_AGG_PG_TH:
		val8 = *val;
		break;

#ifdef CONFIG_WOWLAN
	case HW_VAR_WOWLAN:
	{
		poidparam = (struct wowlan_ioctl_param *)val;
		switch (poidparam->subcode) {
		case WOWLAN_ENABLE:
			DBG_871X_LEVEL(_drv_always_, "WOWLAN_ENABLE\n");

			/* backup data rate to register 0x8b for wowlan FW */
			rtw_write8(padapter, 0x8d, 1);
			rtw_write8(padapter, 0x8c, 0);
			rtw_write8(padapter, 0x8f, 0x40);
			rtw_write8(padapter, 0x8b,
			rtw_read8(padapter, 0x2f0));

			/*  1. Download WOWLAN FW */
			DBG_871X_LEVEL(_drv_always_, "Re-download WoWlan FW!\n");
			SetFwRelatedForWoWLAN8723b(padapter, true);

			/*  2. RX DMA stop */
			DBG_871X_LEVEL(_drv_always_, "Pause DMA\n");
			rtw_write32(padapter, REG_RXPKT_NUM, (rtw_read32(padapter, REG_RXPKT_NUM)|RW_RELEASE_EN));
			do {
				if ((rtw_read32(padapter, REG_RXPKT_NUM)&RXDMA_IDLE)) {
					DBG_871X_LEVEL(_drv_always_, "RX_DMA_IDLE is true\n");
					break;
				} else {
					/*  If RX_DMA is not idle, receive one pkt from DMA */
					res = sdio_local_read(padapter, SDIO_REG_RX0_REQ_LEN, 4, (u8 *)&tmp);
					len = le16_to_cpu(tmp);
					DBG_871X_LEVEL(_drv_always_, "RX len:%d\n", len);
					if (len > 0)
						res = RecvOnePkt(padapter, len);
					else
						DBG_871X_LEVEL(_drv_always_, "read length fail %d\n", len);

					DBG_871X_LEVEL(_drv_always_, "RecvOnePkt Result: %d\n", res);
				}
			} while (trycnt--);
			if (trycnt == 0)
				DBG_871X_LEVEL(_drv_always_, "Stop RX DMA failed......\n");

			/*  3. Clear IMR and ISR */
			DBG_871X_LEVEL(_drv_always_, "Clear IMR and ISR\n");
			tmp = 0;
			sdio_local_write(padapter, SDIO_REG_HIMR_ON, 4, (u8 *)&tmp);
			sdio_local_write(padapter, SDIO_REG_HIMR, 4, (u8 *)&tmp);
			sdio_local_read(padapter, SDIO_REG_HISR, 4, (u8 *)&tmp);
			sdio_local_write(padapter, SDIO_REG_HISR, 4, (u8 *)&tmp);

			/*  4. Enable CPWM2 only */
			DBG_871X_LEVEL(_drv_always_, "Enable only CPWM2\n");
			sdio_local_read(padapter, SDIO_REG_HIMR, 4, (u8 *)&tmp);
			DBG_871X("DisableInterruptButCpwm28723BSdio(): Read SDIO_REG_HIMR: 0x%08x\n", tmp);

			himr = cpu_to_le32(SDIO_HIMR_DISABLED)|SDIO_HIMR_CPWM2_MSK;
			sdio_local_write(padapter, SDIO_REG_HIMR, 4, (u8 *)&himr);

			sdio_local_read(padapter, SDIO_REG_HIMR, 4, (u8 *)&tmp);
			DBG_871X("DisableInterruptButCpwm28723BSdio(): Read again SDIO_REG_HIMR: 0x%08x\n", tmp);

			/*  5. Set Enable WOWLAN H2C command. */
			DBG_871X_LEVEL(_drv_always_, "Set Enable WOWLan cmd\n");
			rtl8723b_set_wowlan_cmd(padapter, 1);

			/*  6. Check EnableWoWlan CMD is ready */
			if (!pwrctl->wowlan_pno_enable) {
				DBG_871X_LEVEL(_drv_always_, "Check EnableWoWlan CMD is ready\n");
				mstatus = rtw_read8(padapter, REG_WOW_CTRL);
				trycnt = 10;
				while (!(mstatus&BIT1) && trycnt > 1) {
					mstatus = rtw_read8(padapter, REG_WOW_CTRL);
					DBG_871X("Loop index: %d :0x%02x\n", trycnt, mstatus);
					trycnt--;
					msleep(2);
				}
			}
			break;

		case WOWLAN_DISABLE:
			DBG_871X_LEVEL(_drv_always_, "WOWLAN_DISABLE\n");

			psta = rtw_get_stainfo(&padapter->stapriv, get_bssid(pmlmepriv));
			if (psta != NULL)
				rtl8723b_set_FwMediaStatusRpt_cmd(padapter, RT_MEDIA_DISCONNECT, psta->mac_id);
			else
				DBG_871X("psta is null\n");

			/*  1. Read wakeup reason */
			pwrctl->wowlan_wake_reason = rtw_read8(padapter, REG_WOWLAN_WAKE_REASON);
			DBG_871X_LEVEL(
				_drv_always_,
				"wakeup_reason: 0x%02x, mac_630 = 0x%08x, mac_634 = 0x%08x, mac_1c0 = 0x%08x, mac_1c4 = 0x%08x"
				", mac_494 = 0x%08x, , mac_498 = 0x%08x, mac_49c = 0x%08x, mac_608 = 0x%08x, mac_4a0 = 0x%08x, mac_4a4 = 0x%08x\n"
				", mac_1cc = 0x%08x, mac_2f0 = 0x%08x, mac_2f4 = 0x%08x, mac_2f8 = 0x%08x, mac_2fc = 0x%08x, mac_8c = 0x%08x",
				pwrctl->wowlan_wake_reason,
				rtw_read32(padapter, REG_WOWLAN_GTK_DBG1),
				rtw_read32(padapter, REG_WOWLAN_GTK_DBG2),
				rtw_read32(padapter, 0x1c0),
				rtw_read32(padapter, 0x1c4),
				rtw_read32(padapter, 0x494),
				rtw_read32(padapter, 0x498),
				rtw_read32(padapter, 0x49c),
				rtw_read32(padapter, 0x608),
				rtw_read32(padapter, 0x4a0),
				rtw_read32(padapter, 0x4a4),
				rtw_read32(padapter, 0x1cc),
				rtw_read32(padapter, 0x2f0),
				rtw_read32(padapter, 0x2f4),
				rtw_read32(padapter, 0x2f8),
				rtw_read32(padapter, 0x2fc),
				rtw_read32(padapter, 0x8c)
			);
#ifdef CONFIG_PNO_SET_DEBUG
			DBG_871X("0x1b9: 0x%02x, 0x632: 0x%02x\n", rtw_read8(padapter, 0x1b9), rtw_read8(padapter, 0x632));
			DBG_871X("0x4fc: 0x%02x, 0x4fd: 0x%02x\n", rtw_read8(padapter, 0x4fc), rtw_read8(padapter, 0x4fd));
			DBG_871X("TXDMA STATUS: 0x%08x\n", rtw_read32(padapter, REG_TXDMA_STATUS));
#endif

			{
				/*  2.  Set Disable WOWLAN H2C command. */
				DBG_871X_LEVEL(_drv_always_, "Set Disable WOWLan cmd\n");
				rtl8723b_set_wowlan_cmd(padapter, 0);

				/*  3. Check Disable WoWlan CMD ready. */
				DBG_871X_LEVEL(_drv_always_, "Check DisableWoWlan CMD is ready\n");
				mstatus = rtw_read8(padapter, REG_WOW_CTRL);
				trycnt = 50;
				while (mstatus&BIT1 && trycnt > 1) {
					mstatus = rtw_read8(padapter, REG_WOW_CTRL);
					DBG_871X_LEVEL(_drv_always_, "Loop index: %d :0x%02x\n", trycnt, mstatus);
					trycnt--;
					msleep(10);
				}

				if (mstatus & BIT1) {
					DBG_871X_LEVEL(_drv_always_, "Disable WOW mode fail!!\n");
					DBG_871X("Set 0x690 = 0x00\n");
					rtw_write8(padapter, REG_WOW_CTRL, (rtw_read8(padapter, REG_WOW_CTRL)&0xf0));
					DBG_871X_LEVEL(_drv_always_, "Release RXDMA\n");
					rtw_write32(padapter, REG_RXPKT_NUM, (rtw_read32(padapter, REG_RXPKT_NUM)&(~RW_RELEASE_EN)));
				}

				/*  3.1 read fw iv */
				iv_low = rtw_read32(padapter, REG_TXPKTBUF_IV_LOW);
					/* only low two bytes is PN, check AES_IV macro for detail */
				iv_low &= 0xffff;
				iv_high = rtw_read32(padapter, REG_TXPKTBUF_IV_HIGH);
					/* get the real packet number */
				pwrctl->wowlan_fw_iv = iv_high << 16 | iv_low;
				DBG_871X_LEVEL(_drv_always_, "fw_iv: 0x%016llx\n", pwrctl->wowlan_fw_iv);
				/* Update TX iv data. */
				rtw_set_sec_pn(padapter);

				/*  3.2 read GTK index and key */
				if (
					psecuritypriv->binstallKCK_KEK == true &&
					psecuritypriv->dot11PrivacyAlgrthm == _AES_
				) {
					u8 gtk_keyindex = 0;
					u8 get_key[16];
					/* read gtk key index */
					gtk_keyindex = rtw_read8(padapter, 0x48c);

					if (gtk_keyindex < 4) {
						psecuritypriv->dot118021XGrpKeyid = gtk_keyindex;
						read_cam(padapter, gtk_keyindex, get_key);
						memcpy(psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].skey, get_key, 16);
						DBG_871X_LEVEL(
							_drv_always_,
							"GTK (%d) = 0x%08x, 0x%08x, 0x%08x, 0x%08x\n",
							gtk_keyindex,
							psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].lkey[0],
							psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].lkey[1],
							psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].lkey[2],
							psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].lkey[3]
						);
					} else
						DBG_871X_LEVEL(_drv_always_, "GTK index =%d\n", gtk_keyindex);
				}

				/*  4. Re-download Normal FW. */
				DBG_871X_LEVEL(_drv_always_, "Re-download Normal FW!\n");
				SetFwRelatedForWoWLAN8723b(padapter, false);
			}
#ifdef CONFIG_GPIO_WAKEUP
			DBG_871X_LEVEL(_drv_always_, "Set Wake GPIO to high for default.\n");
			HalSetOutPutGPIO(padapter, WAKEUP_GPIO_IDX, 1);
#endif

			/*  5. Download reserved pages and report media status if needed. */
			if (
				(pwrctl->wowlan_wake_reason != FWDecisionDisconnect) &&
				(pwrctl->wowlan_wake_reason != Rx_Pairwisekey) &&
				(pwrctl->wowlan_wake_reason != Rx_DisAssoc) &&
				(pwrctl->wowlan_wake_reason != Rx_DeAuth)
			) {
				rtl8723b_set_FwJoinBssRpt_cmd(padapter, RT_MEDIA_CONNECT);
				if (psta != NULL)
					rtl8723b_set_FwMediaStatusRpt_cmd(padapter, RT_MEDIA_CONNECT, psta->mac_id);
			}
#ifdef CONFIG_PNO_SUPPORT
			rtw_write8(padapter, 0x1b8, 0);
			DBG_871X("reset 0x1b8: %d\n", rtw_read8(padapter, 0x1b8));
			rtw_write8(padapter, 0x1b9, 0);
			DBG_871X("reset 0x1b9: %d\n", rtw_read8(padapter, 0x1b9));
			rtw_write8(padapter, REG_PNO_STATUS, 0);
			DBG_871X("reset REG_PNO_STATUS: %d\n", rtw_read8(padapter, REG_PNO_STATUS));
#endif
			break;

		default:
			break;
		}
	}
	break;
#endif /* CONFIG_WOWLAN */
#ifdef CONFIG_AP_WOWLAN
	case HW_VAR_AP_WOWLAN:
	{
		poidparam = (struct wowlan_ioctl_param *)val;
		switch (poidparam->subcode) {
		case WOWLAN_AP_ENABLE:
			DBG_871X("%s, WOWLAN_AP_ENABLE\n", __func__);
			/*  1. Download WOWLAN FW */
			DBG_871X_LEVEL(_drv_always_, "Re-download WoWlan FW!\n");
			SetFwRelatedForWoWLAN8723b(padapter, true);

			/*  2. RX DMA stop */
			DBG_871X_LEVEL(_drv_always_, "Pause DMA\n");
			rtw_write32(padapter, REG_RXPKT_NUM,
				(rtw_read32(padapter, REG_RXPKT_NUM)|RW_RELEASE_EN));
			do {
				if ((rtw_read32(padapter, REG_RXPKT_NUM)&RXDMA_IDLE)) {
					DBG_871X_LEVEL(_drv_always_, "RX_DMA_IDLE is true\n");
					break;
				} else {
					/*  If RX_DMA is not idle, receive one pkt from DMA */
					res = sdio_local_read(padapter, SDIO_REG_RX0_REQ_LEN, 4, (u8 *)&tmp);
					len = le16_to_cpu(tmp);

					DBG_871X_LEVEL(_drv_always_, "RX len:%d\n", len);
					if (len > 0)
						res = RecvOnePkt(padapter, len);
					else
						DBG_871X_LEVEL(_drv_always_, "read length fail %d\n", len);

					DBG_871X_LEVEL(_drv_always_, "RecvOnePkt Result: %d\n", res);
				}
			} while (trycnt--);

			if (trycnt == 0)
				DBG_871X_LEVEL(_drv_always_, "Stop RX DMA failed......\n");

			/*  3. Clear IMR and ISR */
			DBG_871X_LEVEL(_drv_always_, "Clear IMR and ISR\n");
			tmp = 0;
			sdio_local_write(padapter, SDIO_REG_HIMR_ON, 4, (u8 *)&tmp);
			sdio_local_write(padapter, SDIO_REG_HIMR, 4, (u8 *)&tmp);
			sdio_local_read(padapter, SDIO_REG_HISR, 4, (u8 *)&tmp);
			sdio_local_write(padapter, SDIO_REG_HISR, 4, (u8 *)&tmp);

			/*  4. Enable CPWM2 only */
			DBG_871X_LEVEL(_drv_always_, "Enable only CPWM2\n");
			sdio_local_read(padapter, SDIO_REG_HIMR, 4, (u8 *)&tmp);
			DBG_871X("DisableInterruptButCpwm28723BSdio(): Read SDIO_REG_HIMR: 0x%08x\n", tmp);

			himr = cpu_to_le32(SDIO_HIMR_DISABLED)|SDIO_HIMR_CPWM2_MSK;
			sdio_local_write(padapter, SDIO_REG_HIMR, 4, (u8 *)&himr);

			sdio_local_read(padapter, SDIO_REG_HIMR, 4, (u8 *)&tmp);
			DBG_871X("DisableInterruptButCpwm28723BSdio(): Read again SDIO_REG_HIMR: 0x%08x\n", tmp);

			/*  5. Set Enable WOWLAN H2C command. */
			DBG_871X_LEVEL(_drv_always_, "Set Enable AP WOWLan cmd\n");
			rtl8723b_set_ap_wowlan_cmd(padapter, 1);
			/*  6. add some delay for H2C cmd ready */
			msleep(10);

			rtw_write8(padapter, REG_WOWLAN_WAKE_REASON, 0);
			break;
		case WOWLAN_AP_DISABLE:
			DBG_871X("%s, WOWLAN_AP_DISABLE\n", __func__);
			/*  1. Read wakeup reason */
			pwrctl->wowlan_wake_reason =
				rtw_read8(padapter, REG_WOWLAN_WAKE_REASON);

			DBG_871X_LEVEL(_drv_always_, "wakeup_reason: 0x%02x\n",
					pwrctl->wowlan_wake_reason);

			/*  2.  Set Disable WOWLAN H2C command. */
			DBG_871X_LEVEL(_drv_always_, "Set Disable WOWLan cmd\n");
			rtl8723b_set_ap_wowlan_cmd(padapter, 0);
			/*  6. add some delay for H2C cmd ready */
			msleep(2);

			DBG_871X_LEVEL(_drv_always_, "Release RXDMA\n");

			rtw_write32(padapter, REG_RXPKT_NUM,
				(rtw_read32(padapter, REG_RXPKT_NUM) & (~RW_RELEASE_EN)));

			SetFwRelatedForWoWLAN8723b(padapter, false);

#ifdef CONFIG_GPIO_WAKEUP
		DBG_871X_LEVEL(_drv_always_, "Set Wake GPIO to high for default.\n");
		HalSetOutPutGPIO(padapter, WAKEUP_GPIO_IDX, 1);
#endif /* CONFIG_GPIO_WAKEUP */
		rtl8723b_set_FwJoinBssRpt_cmd(padapter, RT_MEDIA_CONNECT);
		issue_beacon(padapter, 0);
		break;
		default:
			break;
	}
}
	break;
#endif /* CONFIG_AP_WOWLAN */
	case HW_VAR_DM_IN_LPS:
		rtl8723b_hal_dm_in_lps(padapter);
		break;
	default:
		SetHwReg8723B(padapter, variable, val);
		break;
	}
}