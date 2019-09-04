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
struct netlbl_unlhsh_iface {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  addr4_list; } ;
struct netlbl_unlhsh_addr4 {int /*<<< orphan*/  secid; } ;
struct netlbl_audit {int dummy; } ;
struct netlbl_af4list {int dummy; } ;
struct net_device {int /*<<< orphan*/ * name; } ;
struct net {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MAC_UNLBL_STCDEL ; 
 int ENOENT ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct netlbl_unlhsh_addr4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlbl_af4list_audit_addr (struct audit_buffer*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netlbl_af4list* netlbl_af4list_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct audit_buffer* netlbl_audit_start_common (int /*<<< orphan*/ ,struct netlbl_audit*) ; 
 struct netlbl_unlhsh_addr4* netlbl_unlhsh_addr4_entry (struct netlbl_af4list*) ; 
 int /*<<< orphan*/  netlbl_unlhsh_lock ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  security_release_secctx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ security_secid_to_secctx (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlbl_unlhsh_remove_addr4(struct net *net,
				      struct netlbl_unlhsh_iface *iface,
				      const struct in_addr *addr,
				      const struct in_addr *mask,
				      struct netlbl_audit *audit_info)
{
	struct netlbl_af4list *list_entry;
	struct netlbl_unlhsh_addr4 *entry;
	struct audit_buffer *audit_buf;
	struct net_device *dev;
	char *secctx;
	u32 secctx_len;

	spin_lock(&netlbl_unlhsh_lock);
	list_entry = netlbl_af4list_remove(addr->s_addr, mask->s_addr,
					   &iface->addr4_list);
	spin_unlock(&netlbl_unlhsh_lock);
	if (list_entry != NULL)
		entry = netlbl_unlhsh_addr4_entry(list_entry);
	else
		entry = NULL;

	audit_buf = netlbl_audit_start_common(AUDIT_MAC_UNLBL_STCDEL,
					      audit_info);
	if (audit_buf != NULL) {
		dev = dev_get_by_index(net, iface->ifindex);
		netlbl_af4list_audit_addr(audit_buf, 1,
					  (dev != NULL ? dev->name : NULL),
					  addr->s_addr, mask->s_addr);
		if (dev != NULL)
			dev_put(dev);
		if (entry != NULL &&
		    security_secid_to_secctx(entry->secid,
					     &secctx, &secctx_len) == 0) {
			audit_log_format(audit_buf, " sec_obj=%s", secctx);
			security_release_secctx(secctx, secctx_len);
		}
		audit_log_format(audit_buf, " res=%u", entry != NULL ? 1 : 0);
		audit_log_end(audit_buf);
	}

	if (entry == NULL)
		return -ENOENT;

	kfree_rcu(entry, rcu);
	return 0;
}