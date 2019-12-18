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
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;
typedef  int /*<<< orphan*/  INT32 ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFAIL ; 
 int /*<<< orphan*/  HCI_CMND_WLAN_IOCTL_SIMPLE_CONFIG_SET_PREFIX ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  SL_SIMPLE_CONFIG_PREFIX_LENGTH ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 wlan_smart_config_set_prefix(CHAR* cNewPrefix)
{
	INT32 ret;
	UINT8 *ptr;
	UINT8 *args;

	ret = EFAIL;
	ptr = tSLInformation.pucTxCommandBuffer;
	args = (ptr + HEADERS_SIZE_CMD);

	if (cNewPrefix == NULL)
		return ret;
	else	// with the new Smart Config, prefix must be TTT
	{
		*cNewPrefix = 'T';
		*(cNewPrefix + 1) = 'T';
		*(cNewPrefix + 2) = 'T';
	}

	ARRAY_TO_STREAM(args, cNewPrefix, SL_SIMPLE_CONFIG_PREFIX_LENGTH);

	hci_command_send(HCI_CMND_WLAN_IOCTL_SIMPLE_CONFIG_SET_PREFIX, ptr, 
		SL_SIMPLE_CONFIG_PREFIX_LENGTH);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_CMND_WLAN_IOCTL_SIMPLE_CONFIG_SET_PREFIX, &ret);

	return(ret);    
}