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
struct oid_par_priv {int dummy; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 

NDIS_STATUS oid_rt_pro_rx_packet_type_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	RT_TRACE(_module_mp_, _drv_err_, ("oid_rt_pro_rx_packet_type_hdl...................\n"));

	if (poid_par_priv->information_buf_len < sizeof (UCHAR)) {
		status = NDIS_STATUS_INVALID_LENGTH;
		*poid_par_priv->bytes_needed = sizeof(UCHAR);
		return status;
	}

	if (poid_par_priv->type_of_oid == SET_OID) {
		Adapter->mppriv.rx_with_status = *(UCHAR *) poid_par_priv->information_buf;
		RT_TRACE(_module_rtl871x_ioctl_c_,_drv_err_, ("Query Information, OID_RT_PRO_RX_PACKET_TYPE:%d \n",\
												Adapter->mppriv.rx_with_status));

		//*(u32 *)&Adapter->eeprompriv.mac_addr[0]=rtw_read32(Adapter, 0x10250050);
		//*(u16 *)&Adapter->eeprompriv.mac_addr[4]=rtw_read16(Adapter, 0x10250054);
		RT_TRACE(_module_rtl871x_ioctl_c_,_drv_err_,("MAC addr=0x%x:0x%x:0x%x:0x%x:0x%x:0x%x  \n",
			Adapter->eeprompriv.mac_addr[0],Adapter->eeprompriv.mac_addr[1],Adapter->eeprompriv.mac_addr[2],\
			Adapter->eeprompriv.mac_addr[3],Adapter->eeprompriv.mac_addr[4],Adapter->eeprompriv.mac_addr[5]));

	}
	else {
		*(UCHAR *) poid_par_priv->information_buf = Adapter->mppriv.rx_with_status;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

		RT_TRACE(_module_rtl871x_ioctl_c_,_drv_err_, ("Query Information, OID_RT_PRO_RX_PACKET_TYPE:%d \n", \
												Adapter->mppriv.rx_with_status));

		//*(u32 *)&Adapter->eeprompriv.mac_addr[0]=rtw_read32(Adapter, 0x10250050);
		//*(u16 *)&Adapter->eeprompriv.mac_addr[4]=rtw_read16(Adapter, 0x10250054);
		RT_TRACE(_module_rtl871x_ioctl_c_,_drv_err_,("MAC addr=0x%x:0x%x:0x%x:0x%x:0x%x:0x%x  \n",
			Adapter->eeprompriv.mac_addr[0],Adapter->eeprompriv.mac_addr[1],Adapter->eeprompriv.mac_addr[2],\
			Adapter->eeprompriv.mac_addr[3],Adapter->eeprompriv.mac_addr[4],Adapter->eeprompriv.mac_addr[5]));
	}
#endif

	return NDIS_STATUS_SUCCESS;
}