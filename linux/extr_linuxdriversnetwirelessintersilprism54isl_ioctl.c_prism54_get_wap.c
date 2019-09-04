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
union oid_res_t {int /*<<< orphan*/  ptr; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  DOT11_OID_BSSID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_wap(struct net_device *ndev, struct iw_request_info *info,
		struct sockaddr *awrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	union oid_res_t r;
	int rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_BSSID, 0, NULL, &r);
	memcpy(awrq->sa_data, r.ptr, ETH_ALEN);
	awrq->sa_family = ARPHRD_ETHER;
	kfree(r.ptr);

	return rvalue;
}