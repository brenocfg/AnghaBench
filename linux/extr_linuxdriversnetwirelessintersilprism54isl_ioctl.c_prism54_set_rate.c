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
union oid_res_t {char* ptr; } ;
typedef  char u32 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; scalar_t__ fixed; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_EXTENDEDRATES ; 
 int /*<<< orphan*/  DOT11_OID_PROFILES ; 
 int /*<<< orphan*/  DOT11_OID_RATES ; 
 int /*<<< orphan*/  DOT11_OID_SUPPORTEDRATES ; 
 int EINVAL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int mgt_set_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_set_rate(struct net_device *ndev,
		 struct iw_request_info *info,
		 struct iw_param *vwrq, char *extra)
{

	islpci_private *priv = netdev_priv(ndev);
	u32 rate, profile;
	char *data;
	int ret, i;
	union oid_res_t r;

	if (vwrq->value == -1) {
		/* auto mode. No limit. */
		profile = 1;
		return mgt_set_request(priv, DOT11_OID_PROFILES, 0, &profile);
	}

	ret = mgt_get_request(priv, DOT11_OID_SUPPORTEDRATES, 0, NULL, &r);
	if (ret) {
		kfree(r.ptr);
		return ret;
	}

	rate = (u32) (vwrq->value / 500000);
	data = r.ptr;
	i = 0;

	while (data[i]) {
		if (rate && (data[i] == rate)) {
			break;
		}
		if (vwrq->value == i) {
			break;
		}
		data[i] |= 0x80;
		i++;
	}

	if (!data[i]) {
		kfree(r.ptr);
		return -EINVAL;
	}

	data[i] |= 0x80;
	data[i + 1] = 0;

	/* Now, check if we want a fixed or auto value */
	if (vwrq->fixed) {
		data[0] = data[i];
		data[1] = 0;
	}

/*
	i = 0;
	printk("prism54 rate: ");
	while(data[i]) {
		printk("%u ", data[i]);
		i++;
	}
	printk("0\n");
*/
	profile = -1;
	ret = mgt_set_request(priv, DOT11_OID_PROFILES, 0, &profile);
	ret |= mgt_set_request(priv, DOT11_OID_EXTENDEDRATES, 0, data);
	ret |= mgt_set_request(priv, DOT11_OID_RATES, 0, data);

	kfree(r.ptr);

	return ret;
}