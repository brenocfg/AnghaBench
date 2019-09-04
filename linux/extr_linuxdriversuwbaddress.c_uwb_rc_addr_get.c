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
struct uwb_rc_evt_dev_addr_mgmt {int /*<<< orphan*/  baAddr; } ;
struct uwb_rc {int dummy; } ;
struct uwb_mac_addr {int* data; } ;
struct uwb_dev_addr {int* data; } ;
typedef  enum uwb_addr_type { ____Placeholder_uwb_addr_type } uwb_addr_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  UWB_ADDR_DEV 129 
#define  UWB_ADDR_MAC 128 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ ,int) ; 
 int uwb_rc_dev_addr_mgmt (struct uwb_rc*,int,int*,struct uwb_rc_evt_dev_addr_mgmt*) ; 

__attribute__((used)) static int uwb_rc_addr_get(struct uwb_rc *rc,
		    void *_addr, enum uwb_addr_type type)
{
	int result;
	u8 bmOperationType = 0x0; 		/* Get address */
	struct uwb_rc_evt_dev_addr_mgmt evt;
	struct uwb_dev_addr *dev_addr = _addr;
	struct uwb_mac_addr *mac_addr = _addr;
	u8 *baAddr;

	result = -EINVAL;
	switch (type) {
	case UWB_ADDR_DEV:
		baAddr = dev_addr->data;
		break;
	case UWB_ADDR_MAC:
		bmOperationType |= 0x2;
		baAddr = mac_addr->data;
		break;
	default:
		return result;
	}
	result = uwb_rc_dev_addr_mgmt(rc, bmOperationType, baAddr, &evt);
	if (result == 0)
		switch (type) {
		case UWB_ADDR_DEV:
			memcpy(&dev_addr->data, evt.baAddr,
			       sizeof(dev_addr->data));
			break;
		case UWB_ADDR_MAC:
			memcpy(&mac_addr->data, evt.baAddr,
			       sizeof(mac_addr->data));
			break;
		default:		/* shut gcc up */
			BUG();
		}
	return result;
}