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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rtw_p2p_get(struct net_device *dev,
                               struct iw_request_info *info,
                               union iwreq_data *wrqu, char *extra)
{
	
	int ret = 0;	
	
#ifdef CONFIG_P2P

	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);	
	struct iw_point *pdata = &wrqu->data;
	struct wifidirect_info *pwdinfo= &(padapter->wdinfo);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;

	if ( padapter->bShowGetP2PState )
	{
		DBG_871X( "[%s] extra = %s\n", __FUNCTION__, (char*) wrqu->data.pointer );
	}
	
	if ( _rtw_memcmp( wrqu->data.pointer, "status", 6 ) )
	{
		rtw_p2p_get_status( dev, info, wrqu, extra );
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "role", 4 ) )
	{
		rtw_p2p_get_role( dev, info, wrqu, extra);
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "peer_ifa", 8 ) )
	{
		rtw_p2p_get_peer_ifaddr( dev, info, wrqu, extra);
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "req_cm", 6 ) )
	{
		rtw_p2p_get_req_cm( dev, info, wrqu, extra);
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "peer_deva", 9 ) )
	{
		//	Get the P2P device address when receiving the provision discovery request frame.
		rtw_p2p_get_peer_devaddr( dev, info, wrqu, extra);
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "group_id", 8 ) )
	{
		rtw_p2p_get_groupid( dev, info, wrqu, extra);
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "inv_peer_deva", 13 ) )
	{
		//	Get the P2P device address when receiving the P2P Invitation request frame.
		rtw_p2p_get_peer_devaddr_by_invitation( dev, info, wrqu, extra);
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "op_ch", 5 ) )
	{
		rtw_p2p_get_op_ch( dev, info, wrqu, extra);
	}
#ifdef CONFIG_WFD
	else if ( _rtw_memcmp( wrqu->data.pointer, "peer_port", 9 ) )
	{
		rtw_p2p_get_peer_wfd_port( dev, info, wrqu, extra );
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "wfd_sa", 6 ) )
	{
		rtw_p2p_get_peer_wfd_session_available( dev, info, wrqu, extra );
	}
	else if ( _rtw_memcmp( wrqu->data.pointer, "wfd_pc", 6 ) )
	{
		rtw_p2p_get_peer_wfd_preferred_connection( dev, info, wrqu, extra );
	}
#endif // CONFIG_WFD	
	
#endif //CONFIG_P2P

	return ret;
		
}