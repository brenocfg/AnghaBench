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
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int proc_get_read_addr ; 
 int proc_get_read_len ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int snprintf (char*,int,char*,int,...) ; 
 int usb_read16 (struct adapter*,int) ; 
 int usb_read32 (struct adapter*,int) ; 
 int usb_read8 (struct adapter*,int) ; 

int proc_get_read_reg(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);

	int len = 0;

	if (proc_get_read_addr == 0xeeeeeeee) {
		*eof = 1;
		return len;
	}

	switch (proc_get_read_len) {
	case 1:
		len += snprintf(page + len, count - len, "usb_read8(0x%x)=0x%x\n", proc_get_read_addr, usb_read8(padapter, proc_get_read_addr));
		break;
	case 2:
		len += snprintf(page + len, count - len, "usb_read16(0x%x)=0x%x\n", proc_get_read_addr, usb_read16(padapter, proc_get_read_addr));
		break;
	case 4:
		len += snprintf(page + len, count - len, "usb_read32(0x%x)=0x%x\n", proc_get_read_addr, usb_read32(padapter, proc_get_read_addr));
		break;
	default:
		len += snprintf(page + len, count - len, "error read length=%d\n", proc_get_read_len);
		break;
	}

	*eof = 1;
	return len;
}