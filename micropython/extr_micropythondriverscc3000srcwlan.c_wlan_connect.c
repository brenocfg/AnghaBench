#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;
typedef  int INT32 ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int CC3000_EXPORT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int EFAIL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  HCI_CMND_WLAN_CONNECT ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UINT32_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ WLAN_CONNECT_PARAM_LEN ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ tSLInformation ; 

INT32 wlan_connect(UINT32 ulSecType, CHAR *ssid, INT32 ssid_len,
	UINT8 *bssid, UINT8 *key, INT32 key_len)
{
	INT32 ret;
	UINT8 *ptr;
	UINT8 *args;
	UINT8 bssid_zero[] = {0, 0, 0, 0, 0, 0};

	ret  	= EFAIL;
	ptr  	= tSLInformation.pucTxCommandBuffer;
	args 	= (ptr + HEADERS_SIZE_CMD);

	// Fill in command buffer
	args = UINT32_TO_STREAM(args, 0x0000001c);
	args = UINT32_TO_STREAM(args, ssid_len);
	args = UINT32_TO_STREAM(args, ulSecType);
	args = UINT32_TO_STREAM(args, 0x00000010 + ssid_len);
	args = UINT32_TO_STREAM(args, key_len);
	args = UINT16_TO_STREAM(args, 0);

	// padding shall be zeroed
	if(bssid)
	{
		ARRAY_TO_STREAM(args, bssid, ETH_ALEN);
	}
	else
	{
		ARRAY_TO_STREAM(args, bssid_zero, ETH_ALEN);
	}

	ARRAY_TO_STREAM(args, ssid, ssid_len);

	if(key_len && key)
	{
		ARRAY_TO_STREAM(args, key, key_len);
	}

	// Initiate a HCI command
	hci_command_send(HCI_CMND_WLAN_CONNECT, ptr, WLAN_CONNECT_PARAM_LEN + 
		ssid_len + key_len - 1);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_CMND_WLAN_CONNECT, &ret);
	CC3000_EXPORT(errno) = ret;

	return(ret);
}