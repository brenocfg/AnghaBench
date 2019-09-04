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
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  _rtw_memcpy (char*,int /*<<< orphan*/ ,int) ; 

int rtw_android_get_p2p_dev_addr(struct net_device *net, char *command, int total_len)
{
	int bytes_written = 0;

	//We use the same address as our HW MAC address
	_rtw_memcpy(command, net->dev_addr, ETH_ALEN);
	
	bytes_written = ETH_ALEN;
	return bytes_written;
}