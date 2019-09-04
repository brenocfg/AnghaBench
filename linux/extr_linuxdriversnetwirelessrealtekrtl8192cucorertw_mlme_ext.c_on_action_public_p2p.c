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
struct TYPE_3__ {unsigned char* rx_data; int /*<<< orphan*/  len; int /*<<< orphan*/ * adapter; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  uint ;
typedef  unsigned char u8 ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 scalar_t__ _FAIL ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  merged_p2p_ielen ; 
 scalar_t__ merged_p2pie ; 
 scalar_t__ rtw_action_public_decache (union recv_frame*,unsigned char) ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__,int /*<<< orphan*/ ) ; 

unsigned int on_action_public_p2p(union recv_frame *precv_frame)
{
	_adapter *padapter = precv_frame->u.hdr.adapter;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint len = precv_frame->u.hdr.len;
	u8 *frame_body;
	u8 dialogToken=0;
#ifdef CONFIG_P2P
	u8 *p2p_ie;
	u32	p2p_ielen, wps_ielen;
	struct	wifidirect_info	*pwdinfo = &( padapter->wdinfo );
	u8	result = P2P_STATUS_SUCCESS;
	u8	empty_addr[ETH_ALEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	u8 *merged_p2pie = NULL;
	u32 merged_p2p_ielen = 0;
#endif //CONFIG_P2P

	frame_body = (unsigned char *)(pframe + sizeof(struct rtw_ieee80211_hdr_3addr));

	dialogToken = frame_body[7];

	if (rtw_action_public_decache(precv_frame, dialogToken) == _FAIL)
		return _FAIL;
	
#ifdef CONFIG_P2P
	_cancel_timer_ex( &pwdinfo->reset_ch_sitesurvey );
#ifdef CONFIG_IOCTL_CFG80211
	if(wdev_to_priv(padapter->rtw_wdev)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211)
	{
		rtw_cfg80211_rx_p2p_action_public(padapter, pframe, len);
	}
	else
#endif //CONFIG_IOCTL_CFG80211
	{
		//	Do nothing if the driver doesn't enable the P2P function.
		if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE) || rtw_p2p_chk_state(pwdinfo, P2P_STATE_IDLE))
			return _SUCCESS;

		len -= sizeof(struct rtw_ieee80211_hdr_3addr);

		switch( frame_body[ 6 ] )//OUI Subtype
		{
			case P2P_GO_NEGO_REQ:
			{
				DBG_871X( "[%s] Got GO Nego Req Frame\n", __FUNCTION__);
				_rtw_memset( &pwdinfo->groupid_info, 0x00, sizeof( struct group_id_info ) );

				if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_RX_PROVISION_DIS_REQ))
				{
					rtw_p2p_set_state(pwdinfo, rtw_p2p_pre_state(pwdinfo));
				}

				if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_GONEGO_FAIL))
				{
					//	Commented by Albert 20110526
					//	In this case, this means the previous nego fail doesn't be reset yet.
					_cancel_timer_ex( &pwdinfo->restore_p2p_state_timer );
					//	Restore the previous p2p state
					rtw_p2p_set_state(pwdinfo, rtw_p2p_pre_state(pwdinfo));
					DBG_871X( "[%s] Restore the previous p2p state to %d\n", __FUNCTION__, rtw_p2p_state(pwdinfo) );						
				}					
#ifdef CONFIG_CONCURRENT_MODE
				if ( check_buddy_fwstate(padapter, _FW_LINKED ) )
				{
					_cancel_timer_ex( &pwdinfo->ap_p2p_switch_timer );
				}
#endif // CONFIG_CONCURRENT_MODE

				//	Commented by Kurt 20110902
				//Add if statement to avoid receiving duplicate prov disc req. such that pre_p2p_state would be covered.
				if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_GONEGO_ING))
					rtw_p2p_set_pre_state(pwdinfo, rtw_p2p_state(pwdinfo));

				//	Commented by Kurt 20120113
				//	Get peer_dev_addr here if peer doesn't issue prov_disc frame.
				if( _rtw_memcmp(pwdinfo->rx_prov_disc_info.peerDevAddr, empty_addr, ETH_ALEN) )
					_rtw_memcpy(pwdinfo->rx_prov_disc_info.peerDevAddr, GetAddr2Ptr(pframe), ETH_ALEN);

				result = process_p2p_group_negotation_req( pwdinfo, frame_body, len );
				issue_p2p_GO_response( padapter, GetAddr2Ptr(pframe), frame_body, len, result );
#ifdef CONFIG_INTEL_WIDI
				if( (padapter->mlmepriv.widi_state == INTEL_WIDI_STATE_LISTEN) && (padapter->mlmepriv.widi_state != INTEL_WIDI_STATE_WFD_CONNECTION) )
				{
					padapter->mlmepriv.widi_state = INTEL_WIDI_STATE_WFD_CONNECTION;
					_cancel_timer_ex(&(padapter->mlmepriv.listen_timer));
					intel_widi_wk_cmd(padapter, INTEL_WIDI_LISTEN_STOP_WK, NULL);
				}
#endif //CONFIG_INTEL_WIDI

				//	Commented by Albert 20110718
				//	No matter negotiating or negotiation failure, the driver should set up the restore P2P state timer.
#ifdef CONFIG_CONCURRENT_MODE
				//	Commented by Albert 20120107
				_set_timer( &pwdinfo->restore_p2p_state_timer, 3000 );
#else // CONFIG_CONCURRENT_MODE
				_set_timer( &pwdinfo->restore_p2p_state_timer, 5000 );
#endif // CONFIG_CONCURRENT_MODE
				break;					
			}
			case P2P_GO_NEGO_RESP:
			{
				DBG_871X( "[%s] Got GO Nego Resp Frame\n", __FUNCTION__);

				if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_GONEGO_ING))
				{
					//	Commented by Albert 20110425
					//	The restore timer is enabled when issuing the nego request frame of rtw_p2p_connect function.
					_cancel_timer_ex( &pwdinfo->restore_p2p_state_timer );
					pwdinfo->nego_req_info.benable = _FALSE;
					result = process_p2p_group_negotation_resp( pwdinfo, frame_body, len);
					issue_p2p_GO_confirm( pwdinfo->padapter, GetAddr2Ptr(pframe), result);
					if ( P2P_STATUS_SUCCESS == result )
					{
						if ( rtw_p2p_role(pwdinfo) == P2P_ROLE_CLIENT )
						{
							pwdinfo->p2p_info.operation_ch[ 0 ] = pwdinfo->peer_operating_ch;
							#ifdef P2P_OP_CHECK_SOCIAL_CH
							pwdinfo->p2p_info.operation_ch[ 1 ] = 1;	//Check whether GO is operating in channel 1;
							pwdinfo->p2p_info.operation_ch[ 2 ] = 6;	//Check whether GO is operating in channel 6;
							pwdinfo->p2p_info.operation_ch[ 3 ] = 11;	//Check whether GO is operating in channel 11;
							#endif //P2P_OP_CHECK_SOCIAL_CH
							pwdinfo->p2p_info.scan_op_ch_only = 1;
							_set_timer( &pwdinfo->reset_ch_sitesurvey2, P2P_RESET_SCAN_CH );
						}
 					}

					//	Reset the dialog token for group negotiation frames.
					pwdinfo->negotiation_dialog_token = 1;

					if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_GONEGO_FAIL))
					{
						_set_timer( &pwdinfo->restore_p2p_state_timer, 5000 );
					}
				}
				else
				{
					DBG_871X( "[%s] Skipped GO Nego Resp Frame (p2p_state != P2P_STATE_GONEGO_ING)\n", __FUNCTION__);
				}
						
				break;
			}
			case P2P_GO_NEGO_CONF:
			{
				DBG_871X( "[%s] Got GO Nego Confirm Frame\n", __FUNCTION__);
				result = process_p2p_group_negotation_confirm( pwdinfo, frame_body, len);
				if ( P2P_STATUS_SUCCESS == result )
				{
					if ( rtw_p2p_role(pwdinfo) == P2P_ROLE_CLIENT )
					{
						pwdinfo->p2p_info.operation_ch[ 0 ] = pwdinfo->peer_operating_ch;
						#ifdef P2P_OP_CHECK_SOCIAL_CH
						pwdinfo->p2p_info.operation_ch[ 1 ] = 1;	//Check whether GO is operating in channel 1;
						pwdinfo->p2p_info.operation_ch[ 2 ] = 6;	//Check whether GO is operating in channel 6;
						pwdinfo->p2p_info.operation_ch[ 3 ] = 11;	//Check whether GO is operating in channel 11;
						#endif //P2P_OP_CHECK_SOCIAL_CH
						pwdinfo->p2p_info.scan_op_ch_only = 1;
						_set_timer( &pwdinfo->reset_ch_sitesurvey2, P2P_RESET_SCAN_CH );
					}
 				}
				break;
			}
			case P2P_INVIT_REQ:
			{
				//	Added by Albert 2010/10/05
				//	Received the P2P Invite Request frame.
						
				DBG_871X( "[%s] Got invite request frame!\n", __FUNCTION__ );
				if ( (p2p_ie=rtw_get_p2p_ie( frame_body + _PUBLIC_ACTION_IE_OFFSET_, len - _PUBLIC_ACTION_IE_OFFSET_, NULL, &p2p_ielen)) )
				{
					//	Parse the necessary information from the P2P Invitation Request frame.
					//	For example: The MAC address of sending this P2P Invitation Request frame.
					u32	attr_contentlen = 0;
					u8	status_code = P2P_STATUS_FAIL_INFO_UNAVAILABLE;
					struct group_id_info group_id;
					u8	invitation_flag = 0;

					merged_p2p_ielen = rtw_get_p2p_merged_ies_len(frame_body + _PUBLIC_ACTION_IE_OFFSET_, len - _PUBLIC_ACTION_IE_OFFSET_);

					merged_p2pie = rtw_malloc(merged_p2p_ielen);
					if (merged_p2pie == NULL)
					{
						DBG_871X( "[%s] Malloc p2p ie fail\n", __FUNCTION__);
						goto exit;
					}
					_rtw_memset(merged_p2pie, 0x00, merged_p2p_ielen);					

					merged_p2p_ielen = rtw_p2p_merge_ies(frame_body + _PUBLIC_ACTION_IE_OFFSET_, len - _PUBLIC_ACTION_IE_OFFSET_, merged_p2pie);

					rtw_get_p2p_attr_content( merged_p2pie, merged_p2p_ielen, P2P_ATTR_INVITATION_FLAGS, &invitation_flag, &attr_contentlen);
					if ( attr_contentlen )
					{

						rtw_get_p2p_attr_content( merged_p2pie, merged_p2p_ielen, P2P_ATTR_GROUP_BSSID, pwdinfo->p2p_peer_interface_addr, &attr_contentlen);
						//	Commented by Albert 20120510
						//	Copy to the pwdinfo->p2p_peer_interface_addr.
						//	So that the WFD UI ( or Sigma ) can get the peer interface address by using the following command.
						//	#> iwpriv wlan0 p2p_get peer_ifa
						//	After having the peer interface address, the sigma can find the correct conf file for wpa_supplicant.

						if ( attr_contentlen )
						{
							DBG_871X( "[%s] GO's BSSID = %.2X %.2X %.2X %.2X %.2X %.2X\n", __FUNCTION__,
									pwdinfo->p2p_peer_interface_addr[0], pwdinfo->p2p_peer_interface_addr[1],
									pwdinfo->p2p_peer_interface_addr[2], pwdinfo->p2p_peer_interface_addr[3],
									pwdinfo->p2p_peer_interface_addr[4], pwdinfo->p2p_peer_interface_addr[5] );
						}								

						if ( invitation_flag & P2P_INVITATION_FLAGS_PERSISTENT )
						{
							//	Re-invoke the persistent group.
							
							_rtw_memset( &group_id, 0x00, sizeof( struct group_id_info ) );
							rtw_get_p2p_attr_content( merged_p2pie, merged_p2p_ielen, P2P_ATTR_GROUP_ID, ( u8* ) &group_id, &attr_contentlen);
							if ( attr_contentlen )
							{
								if ( _rtw_memcmp( group_id.go_device_addr, myid( &padapter->eeprompriv ), ETH_ALEN ) )
								{
									//	The p2p device sending this p2p invitation request wants this Wi-Fi device to be the persistent GO.
									rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_GO );
									rtw_p2p_set_role( pwdinfo, P2P_ROLE_GO );
									status_code = P2P_STATUS_SUCCESS;
								}
								else
								{
									//	The p2p device sending this p2p invitation request wants to be the persistent GO.
									if ( is_matched_in_profilelist( pwdinfo->p2p_peer_interface_addr, &pwdinfo->profileinfo[ 0 ] ) )
									{
										u8 operatingch_info[5] = { 0x00 };

										if ( rtw_get_p2p_attr_content(merged_p2pie, merged_p2p_ielen, P2P_ATTR_OPERATING_CH, operatingch_info, &attr_contentlen) )
										{
											if( rtw_ch_set_search_ch(padapter->mlmeextpriv.channel_set, (u32)operatingch_info[4] ) >= 0 )
											{
												//	The operating channel is acceptable for this device.
												pwdinfo->rx_invitereq_info.operation_ch[0]= operatingch_info[4];
												#ifdef P2P_OP_CHECK_SOCIAL_CH
												pwdinfo->rx_invitereq_info.operation_ch[1]= 1;		//Check whether GO is operating in channel 1;
												pwdinfo->rx_invitereq_info.operation_ch[2]= 6;		//Check whether GO is operating in channel 6;
												pwdinfo->rx_invitereq_info.operation_ch[3]= 11;		//Check whether GO is operating in channel 11;
												#endif //P2P_OP_CHECK_SOCIAL_CH
												pwdinfo->rx_invitereq_info.scan_op_ch_only = 1;
												_set_timer( &pwdinfo->reset_ch_sitesurvey, P2P_RESET_SCAN_CH );
												rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_MATCH );
												rtw_p2p_set_role( pwdinfo, P2P_ROLE_CLIENT );
												status_code = P2P_STATUS_SUCCESS;
											}
											else
											{
												//	The operating channel isn't supported by this device.
												rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_DISMATCH );
												rtw_p2p_set_role( pwdinfo, P2P_ROLE_DEVICE );
												status_code = P2P_STATUS_FAIL_NO_COMMON_CH;
												_set_timer( &pwdinfo->restore_p2p_state_timer, 3000 );
											}
										}
										else
										{
											//	Commented by Albert 20121130
											//	Intel will use the different P2P IE to store the operating channel information
											//	Workaround for Intel WiDi 3.5
											rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_MATCH );
											rtw_p2p_set_role( pwdinfo, P2P_ROLE_CLIENT );
											status_code = P2P_STATUS_SUCCESS;
										}
									}
									else
									{
										rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_DISMATCH );
										#ifdef CONFIG_INTEL_WIDI
										_rtw_memcpy( pwdinfo->p2p_peer_device_addr, group_id.go_device_addr , ETH_ALEN );
										rtw_p2p_set_role( pwdinfo, P2P_ROLE_CLIENT );
										#endif //CONFIG_INTEL_WIDI

										status_code = P2P_STATUS_FAIL_UNKNOWN_P2PGROUP;
									}
								}
							}
							else
							{
								DBG_871X( "[%s] P2P Group ID Attribute NOT FOUND!\n", __FUNCTION__ );
								status_code = P2P_STATUS_FAIL_INFO_UNAVAILABLE;
							}									
						}
						else
						{
							//	Received the invitation to join a P2P group.

							_rtw_memset( &group_id, 0x00, sizeof( struct group_id_info ) );
							rtw_get_p2p_attr_content( merged_p2pie, merged_p2p_ielen, P2P_ATTR_GROUP_ID, ( u8* ) &group_id, &attr_contentlen);
							if ( attr_contentlen )
							{
								if ( _rtw_memcmp( group_id.go_device_addr, myid( &padapter->eeprompriv ), ETH_ALEN ) )
								{
									//	In this case, the GO can't be myself.
									rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_DISMATCH );
									status_code = P2P_STATUS_FAIL_INFO_UNAVAILABLE;
								}
								else
								{
									//	The p2p device sending this p2p invitation request wants to join an existing P2P group
									//	Commented by Albert 2012/06/28
									//	In this case, this Wi-Fi device should use the iwpriv command to get the peer device address.
									//	The peer device address should be the destination address for the provisioning discovery request.
									//	Then, this Wi-Fi device should use the iwpriv command to get the peer interface address.
									//	The peer interface address should be the address for WPS mac address
									_rtw_memcpy( pwdinfo->p2p_peer_device_addr, group_id.go_device_addr , ETH_ALEN );											
									rtw_p2p_set_role( pwdinfo, P2P_ROLE_CLIENT );
									rtw_p2p_set_state(pwdinfo, P2P_STATE_RECV_INVITE_REQ_JOIN );
									status_code = P2P_STATUS_SUCCESS;
								}
							}
							else
							{
								DBG_871X( "[%s] P2P Group ID Attribute NOT FOUND!\n", __FUNCTION__ );
								status_code = P2P_STATUS_FAIL_INFO_UNAVAILABLE;
							}
						}
					}
					else
					{
						DBG_871X( "[%s] P2P Invitation Flags Attribute NOT FOUND!\n", __FUNCTION__ );
						status_code = P2P_STATUS_FAIL_INFO_UNAVAILABLE;
					}							

					DBG_871X( "[%s] status_code = %d\n", __FUNCTION__, status_code );

					pwdinfo->inviteresp_info.token = frame_body[ 7 ];
					issue_p2p_invitation_response( padapter, GetAddr2Ptr(pframe), pwdinfo->inviteresp_info.token, status_code );
					_set_timer( &pwdinfo->restore_p2p_state_timer, 3000 );
				}
#ifdef CONFIG_INTEL_WIDI
				if( (padapter->mlmepriv.widi_state == INTEL_WIDI_STATE_LISTEN) && (padapter->mlmepriv.widi_state != INTEL_WIDI_STATE_WFD_CONNECTION) )
				{
					padapter->mlmepriv.widi_state = INTEL_WIDI_STATE_WFD_CONNECTION;
					_cancel_timer_ex(&(padapter->mlmepriv.listen_timer));
					intel_widi_wk_cmd(padapter, INTEL_WIDI_LISTEN_STOP_WK, NULL);
				}
#endif //CONFIG_INTEL_WIDI
				break;
			}
			case P2P_INVIT_RESP:
			{
				u8	attr_content = 0x00;
				u32	attr_contentlen = 0;
				
				DBG_871X( "[%s] Got invite response frame!\n", __FUNCTION__ );
				_cancel_timer_ex( &pwdinfo->restore_p2p_state_timer );
				if ( (p2p_ie=rtw_get_p2p_ie( frame_body + _PUBLIC_ACTION_IE_OFFSET_, len - _PUBLIC_ACTION_IE_OFFSET_, NULL, &p2p_ielen)) )
				{
					rtw_get_p2p_attr_content(p2p_ie, p2p_ielen, P2P_ATTR_STATUS, &attr_content, &attr_contentlen);
									
					if ( attr_contentlen == 1 )
					{
						DBG_871X( "[%s] Status = %d\n", __FUNCTION__, attr_content );
						pwdinfo->invitereq_info.benable = _FALSE;

						if ( attr_content == P2P_STATUS_SUCCESS )
						{
							if ( _rtw_memcmp( pwdinfo->invitereq_info.go_bssid, myid( &padapter->eeprompriv ), ETH_ALEN ))
							{
								rtw_p2p_set_role(pwdinfo, P2P_ROLE_GO );
							}
							else
							{
								rtw_p2p_set_role(pwdinfo, P2P_ROLE_CLIENT);
							}
							rtw_p2p_set_state( pwdinfo, P2P_STATE_RX_INVITE_RESP_OK );
						}
						else
						{
							rtw_p2p_set_role(pwdinfo, P2P_ROLE_DEVICE);
							rtw_p2p_set_state( pwdinfo, P2P_STATE_RX_INVITE_RESP_FAIL );
						}
					}
					else
					{
						rtw_p2p_set_role(pwdinfo, P2P_ROLE_DEVICE);
						rtw_p2p_set_state( pwdinfo, P2P_STATE_RX_INVITE_RESP_FAIL );
					}
				}
				else
				{
					rtw_p2p_set_role(pwdinfo, P2P_ROLE_DEVICE);
					rtw_p2p_set_state( pwdinfo, P2P_STATE_RX_INVITE_RESP_FAIL );
				}

				if ( rtw_p2p_chk_state( pwdinfo, P2P_STATE_RX_INVITE_RESP_FAIL ) )
				{
					_set_timer( &pwdinfo->restore_p2p_state_timer, 5000 );
				}
				break;
			}
			case P2P_DEVDISC_REQ:

				process_p2p_devdisc_req(pwdinfo, pframe, len);

				break;

			case P2P_DEVDISC_RESP:

				process_p2p_devdisc_resp(pwdinfo, pframe, len);

				break;

			case P2P_PROVISION_DISC_REQ:
				DBG_871X( "[%s] Got Provisioning Discovery Request Frame\n", __FUNCTION__ );
				process_p2p_provdisc_req(pwdinfo, pframe, len);
				_rtw_memcpy(pwdinfo->rx_prov_disc_info.peerDevAddr, GetAddr2Ptr(pframe), ETH_ALEN);

				//20110902 Kurt
				//Add the following statement to avoid receiving duplicate prov disc req. such that pre_p2p_state would be covered.
				if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_RX_PROVISION_DIS_REQ))
					rtw_p2p_set_pre_state(pwdinfo, rtw_p2p_state(pwdinfo));
				
				rtw_p2p_set_state(pwdinfo, P2P_STATE_RX_PROVISION_DIS_REQ);
				_set_timer( &pwdinfo->restore_p2p_state_timer, P2P_PROVISION_TIMEOUT );
#ifdef CONFIG_INTEL_WIDI
				if( (padapter->mlmepriv.widi_state == INTEL_WIDI_STATE_LISTEN) && (padapter->mlmepriv.widi_state != INTEL_WIDI_STATE_WFD_CONNECTION) )
				{
					padapter->mlmepriv.widi_state = INTEL_WIDI_STATE_WFD_CONNECTION;
					_cancel_timer_ex(&(padapter->mlmepriv.listen_timer));
					intel_widi_wk_cmd(padapter, INTEL_WIDI_LISTEN_STOP_WK, NULL);
				}
#endif //CONFIG_INTEL_WIDI
				break;

			case P2P_PROVISION_DISC_RESP:
				//	Commented by Albert 20110707
				//	Should we check the pwdinfo->tx_prov_disc_info.bsent flag here??
				DBG_871X( "[%s] Got Provisioning Discovery Response Frame\n", __FUNCTION__ );
				//	Commented by Albert 20110426
				//	The restore timer is enabled when issuing the provisioing request frame in rtw_p2p_prov_disc function.
				_cancel_timer_ex( &pwdinfo->restore_p2p_state_timer );
				rtw_p2p_set_state(pwdinfo, P2P_STATE_RX_PROVISION_DIS_RSP);
				process_p2p_provdisc_resp(pwdinfo, pframe);
				_set_timer( &pwdinfo->restore_p2p_state_timer, P2P_PROVISION_TIMEOUT );
				break;

		}
	}
#endif //CONFIG_P2P

exit:

	if(merged_p2pie)
	{
		rtw_mfree(merged_p2pie, merged_p2p_ielen);
	}

	return _SUCCESS;
}