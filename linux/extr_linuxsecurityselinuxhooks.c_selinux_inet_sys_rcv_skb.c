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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net {int dummy; } ;
struct common_audit_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF__INGRESS ; 
 int /*<<< orphan*/  NODE__RECVFROM ; 
 int /*<<< orphan*/  SECCLASS_NETIF ; 
 int /*<<< orphan*/  SECCLASS_NODE ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int sel_netif_sid (struct net*,int,int /*<<< orphan*/ *) ; 
 int sel_netnode_sid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_inet_sys_rcv_skb(struct net *ns, int ifindex,
				    char *addrp, u16 family, u32 peer_sid,
				    struct common_audit_data *ad)
{
	int err;
	u32 if_sid;
	u32 node_sid;

	err = sel_netif_sid(ns, ifindex, &if_sid);
	if (err)
		return err;
	err = avc_has_perm(&selinux_state,
			   peer_sid, if_sid,
			   SECCLASS_NETIF, NETIF__INGRESS, ad);
	if (err)
		return err;

	err = sel_netnode_sid(addrp, family, &node_sid);
	if (err)
		return err;
	return avc_has_perm(&selinux_state,
			    peer_sid, node_sid,
			    SECCLASS_NODE, NODE__RECVFROM, ad);
}