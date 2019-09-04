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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_EN_SIX_BYTES ; 
 int /*<<< orphan*/  CRWECR_CONFIG ; 
 int /*<<< orphan*/  CRWECR_NORAML ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_CRWECR ; 
 int /*<<< orphan*/  PLA_IDR ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pla_ocp_write (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_set_mac_address(struct net_device *netdev, void *p)
{
	struct r8152 *tp = netdev_priv(netdev);
	struct sockaddr *addr = p;
	int ret = -EADDRNOTAVAIL;

	if (!is_valid_ether_addr(addr->sa_data))
		goto out1;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out1;

	mutex_lock(&tp->control);

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);
	pla_ocp_write(tp, PLA_IDR, BYTE_EN_SIX_BYTES, 8, addr->sa_data);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);
out1:
	return ret;
}