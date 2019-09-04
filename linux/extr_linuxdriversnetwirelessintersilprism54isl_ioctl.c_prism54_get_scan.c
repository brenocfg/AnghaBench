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
union oid_res_t {struct obj_bsslist* ptr; int /*<<< orphan*/  u; } ;
typedef  int /*<<< orphan*/  u32 ;
struct obj_bsslist {int /*<<< orphan*/ * bsslist; scalar_t__ nr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_BSSLIST ; 
 int /*<<< orphan*/  DOT11_OID_NOISEFLOOR ; 
 int E2BIG ; 
 int IW_EV_ADDR_LEN ; 
 scalar_t__ PRV_STATE_INIT ; 
 scalar_t__ islpci_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct obj_bsslist*) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 char* prism54_translate_bss (struct net_device*,struct iw_request_info*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
prism54_get_scan(struct net_device *ndev, struct iw_request_info *info,
		 struct iw_point *dwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	int i, rvalue;
	struct obj_bsslist *bsslist;
	u32 noise = 0;
	char *current_ev = extra;
	union oid_res_t r;

	if (islpci_get_state(priv) < PRV_STATE_INIT) {
		/* device is not ready, fail gently */
		dwrq->length = 0;
		return 0;
	}

	/* first get the noise value. We will use it to report the link quality */
	rvalue = mgt_get_request(priv, DOT11_OID_NOISEFLOOR, 0, NULL, &r);
	noise = r.u;

	/* Ask the device for a list of known bss.
	* The old API, using SIOCGIWAPLIST, had a hard limit of IW_MAX_AP=64.
	* The new API, using SIOCGIWSCAN, is only limited by the buffer size.
	* WE-14->WE-16, the buffer is limited to IW_SCAN_MAX_DATA bytes.
	* Starting with WE-17, the buffer can be as big as needed.
	* But the device won't repport anything if you change the value
	* of IWMAX_BSS=24. */

	rvalue |= mgt_get_request(priv, DOT11_OID_BSSLIST, 0, NULL, &r);
	bsslist = r.ptr;

	/* ok now, scan the list and translate its info */
	for (i = 0; i < (int) bsslist->nr; i++) {
		current_ev = prism54_translate_bss(ndev, info, current_ev,
						   extra + dwrq->length,
						   &(bsslist->bsslist[i]),
						   noise);

		/* Check if there is space for one more entry */
		if((extra + dwrq->length - current_ev) <= IW_EV_ADDR_LEN) {
			/* Ask user space to try again with a bigger buffer */
			rvalue = -E2BIG;
			break;
		}
	}

	kfree(bsslist);
	dwrq->length = (current_ev - extra);
	dwrq->flags = 0;	/* todo */

	return rvalue;
}