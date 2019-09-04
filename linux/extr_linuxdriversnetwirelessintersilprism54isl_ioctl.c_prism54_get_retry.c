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
union oid_res_t {int u; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_LONGRETRIES ; 
 int /*<<< orphan*/  DOT11_OID_MAXTXLIFETIME ; 
 int /*<<< orphan*/  DOT11_OID_SHORTRETRIES ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_retry(struct net_device *ndev, struct iw_request_info *info,
		  struct iw_param *vwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	union oid_res_t r;
	int rvalue = 0;
	vwrq->disabled = 0;	/* It cannot be disabled */

	if ((vwrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) {
		/* we are asked for the life time */
		rvalue =
		    mgt_get_request(priv, DOT11_OID_MAXTXLIFETIME, 0, NULL, &r);
		vwrq->value = r.u * 1024;
		vwrq->flags = IW_RETRY_LIFETIME;
	} else if ((vwrq->flags & IW_RETRY_LONG)) {
		/* we are asked for the long retry limit */
		rvalue |=
		    mgt_get_request(priv, DOT11_OID_LONGRETRIES, 0, NULL, &r);
		vwrq->value = r.u;
		vwrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
	} else {
		/* default. get the  short retry limit */
		rvalue |=
		    mgt_get_request(priv, DOT11_OID_SHORTRETRIES, 0, NULL, &r);
		vwrq->value = r.u;
		vwrq->flags = IW_RETRY_LIMIT | IW_RETRY_SHORT;
	}

	return rvalue;
}