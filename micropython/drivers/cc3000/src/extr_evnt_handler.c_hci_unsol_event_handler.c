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
typedef  int /*<<< orphan*/  params ;
struct TYPE_3__ {int packets_sent; int packets_received; int min_round_time; int max_round_time; int avg_round_time; } ;
typedef  TYPE_1__ netapp_pingreport_args_t ;
typedef  scalar_t__ event_hdr ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int usRxEventOpcode; int /*<<< orphan*/  slTransmitDataError; int /*<<< orphan*/  (* sWlanCB ) (int,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  InformHostOnTxComplete; int /*<<< orphan*/  NumberOfSentPackets; int /*<<< orphan*/  NumberOfReleasedPackets; } ;
typedef  int INT32 ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_RSP_PARAMS_STATUS_OFFSET ; 
 int ERROR_SOCKET_INACTIVE ; 
 int HCI_EVENT_CC3000_CAN_SHUT_DOWN ; 
 int /*<<< orphan*/  HCI_EVENT_HEADER_SIZE ; 
 int /*<<< orphan*/  HCI_EVENT_OPCODE_OFFSET ; 
 int /*<<< orphan*/  HCI_EVENT_STATUS_OFFSET ; 
#define  HCI_EVNT_BSD_TCP_CLOSE_WAIT 136 
#define  HCI_EVNT_DATA_UNSOL_FREE_BUFF 135 
 int HCI_EVNT_PATCHES_REQ ; 
 int HCI_EVNT_SEND ; 
 int HCI_EVNT_SENDTO ; 
 int HCI_EVNT_UNSOL_BASE ; 
#define  HCI_EVNT_WLAN_ASYNC_PING_REPORT 134 
#define  HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE 133 
#define  HCI_EVNT_WLAN_KEEPALIVE 132 
 int HCI_EVNT_WLAN_UNSOL_BASE ; 
#define  HCI_EVNT_WLAN_UNSOL_CONNECT 131 
#define  HCI_EVNT_WLAN_UNSOL_DHCP 130 
#define  HCI_EVNT_WLAN_UNSOL_DISCONNECT 129 
#define  HCI_EVNT_WLAN_UNSOL_INIT 128 
 int HCI_EVNT_WRITE ; 
 int /*<<< orphan*/ * M_BSD_RESP_PARAMS_OFFSET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NETAPP_IPCONFIG_IP_LENGTH ; 
 int /*<<< orphan*/  NETAPP_IPCONFIG_MAC_OFFSET ; 
 int /*<<< orphan*/  NETAPP_PING_AVG_RTT_OFFSET ; 
 int /*<<< orphan*/  NETAPP_PING_MAX_RTT_OFFSET ; 
 int /*<<< orphan*/  NETAPP_PING_MIN_RTT_OFFSET ; 
 int /*<<< orphan*/  NETAPP_PING_PACKETS_RCVD_OFFSET ; 
 int /*<<< orphan*/  NETAPP_PING_PACKETS_SENT_OFFSET ; 
 int /*<<< orphan*/  STREAM_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STREAM_TO_UINT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_event_unsol_flowcontrol_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ tSLInformation ; 
 int /*<<< orphan*/  update_socket_active_status (int /*<<< orphan*/ *) ; 

INT32 hci_unsol_event_handler(CHAR *event_hdr)
{
	CHAR * data = NULL;
	INT32 event_type;
	UINT32 NumberOfReleasedPackets;
	UINT32 NumberOfSentPackets;

	STREAM_TO_UINT16(event_hdr, HCI_EVENT_OPCODE_OFFSET,event_type);

	if (event_type & HCI_EVNT_UNSOL_BASE)
	{
		switch(event_type)
		{

		case HCI_EVNT_DATA_UNSOL_FREE_BUFF:
			{
				hci_event_unsol_flowcontrol_handler(event_hdr);

				NumberOfReleasedPackets = tSLInformation.NumberOfReleasedPackets;
				NumberOfSentPackets = tSLInformation.NumberOfSentPackets;

				if (NumberOfReleasedPackets == NumberOfSentPackets)
				{
					if (tSLInformation.InformHostOnTxComplete)
					{
						tSLInformation.sWlanCB(HCI_EVENT_CC3000_CAN_SHUT_DOWN, NULL, 0);
					}
				}				
				return 1;

			}
		}
	}

	if(event_type & HCI_EVNT_WLAN_UNSOL_BASE)
	{           
		switch(event_type)
		{
		case HCI_EVNT_WLAN_KEEPALIVE:
		case HCI_EVNT_WLAN_UNSOL_CONNECT:
		case HCI_EVNT_WLAN_UNSOL_DISCONNECT:
		case HCI_EVNT_WLAN_UNSOL_INIT:
		case HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE:

			if( tSLInformation.sWlanCB )
			{
				tSLInformation.sWlanCB(event_type, 0, 0);
			}
			break;

		case HCI_EVNT_WLAN_UNSOL_DHCP:
			{
				UINT8	params[NETAPP_IPCONFIG_MAC_OFFSET + 1];	// extra byte is for the status
				UINT8 *recParams = params;

				data = (CHAR*)(event_hdr) + HCI_EVENT_HEADER_SIZE;

				//Read IP address
				STREAM_TO_STREAM(data,recParams,NETAPP_IPCONFIG_IP_LENGTH);
				data += 4;
				//Read subnet
				STREAM_TO_STREAM(data,recParams,NETAPP_IPCONFIG_IP_LENGTH);
				data += 4;
				//Read default GW
				STREAM_TO_STREAM(data,recParams,NETAPP_IPCONFIG_IP_LENGTH); 
				data += 4;
				//Read DHCP server  
				STREAM_TO_STREAM(data,recParams,NETAPP_IPCONFIG_IP_LENGTH);     
				data += 4;
				//Read DNS server  
				STREAM_TO_STREAM(data,recParams,NETAPP_IPCONFIG_IP_LENGTH); 
				// read the status
				STREAM_TO_UINT8(event_hdr, HCI_EVENT_STATUS_OFFSET, *recParams);


				if( tSLInformation.sWlanCB )
				{
					tSLInformation.sWlanCB(event_type, (CHAR *)params, sizeof(params));
				}
			}
			break;

		case HCI_EVNT_WLAN_ASYNC_PING_REPORT:
			{
				netapp_pingreport_args_t params;			
				data = (CHAR*)(event_hdr) + HCI_EVENT_HEADER_SIZE;			
				STREAM_TO_UINT32(data, NETAPP_PING_PACKETS_SENT_OFFSET, params.packets_sent);			
				STREAM_TO_UINT32(data, NETAPP_PING_PACKETS_RCVD_OFFSET, params.packets_received);			
				STREAM_TO_UINT32(data, NETAPP_PING_MIN_RTT_OFFSET, params.min_round_time);		
				STREAM_TO_UINT32(data, NETAPP_PING_MAX_RTT_OFFSET, params.max_round_time);	
				STREAM_TO_UINT32(data, NETAPP_PING_AVG_RTT_OFFSET, params.avg_round_time);

				if( tSLInformation.sWlanCB )
				{
					tSLInformation.sWlanCB(event_type, (CHAR *)&params, sizeof(params));
				}
			}
			break;
		case HCI_EVNT_BSD_TCP_CLOSE_WAIT:
			{
				data = (CHAR *)(event_hdr) + HCI_EVENT_HEADER_SIZE;
				if( tSLInformation.sWlanCB )
				{
					//data[0] represents the socket id, for which FIN was received by remote.
					//Upon receiving this event, the user can close the socket, or else the 
					//socket will be closded after inacvitity timeout (by default 60 seconds)
					tSLInformation.sWlanCB(event_type, data, 1);
				}
			}
			break;

			//'default' case which means "event not supported" 	
		default: 
			return (0);
		}
		return(1);
	}

	if ((event_type == HCI_EVNT_SEND) || (event_type == HCI_EVNT_SENDTO)
		|| (event_type == HCI_EVNT_WRITE))
	{
		CHAR *pArg;
		INT32 status;

		pArg = M_BSD_RESP_PARAMS_OFFSET(event_hdr);
		STREAM_TO_UINT32(pArg, BSD_RSP_PARAMS_STATUS_OFFSET,status);

		if (ERROR_SOCKET_INACTIVE == status)
		{
			// The only synchronous event that can come from SL device in form of 
			// command complete is "Command Complete" on data sent, in case SL device 
			// was unable to transmit
			STREAM_TO_UINT8(event_hdr, HCI_EVENT_STATUS_OFFSET, tSLInformation.slTransmitDataError);
			update_socket_active_status(M_BSD_RESP_PARAMS_OFFSET(event_hdr));

			return (1);
		}
		else
			return (0);
	}

	//handle a case where unsolicited event arrived, but was not handled by any of the cases above
	if ((event_type != tSLInformation.usRxEventOpcode) && (event_type != HCI_EVNT_PATCHES_REQ))
	{
		return(1);
	}

	return(0);
}