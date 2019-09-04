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
struct socket {int /*<<< orphan*/  sk; } ;
struct smc_clc_msg_proposal_prefix {int /*<<< orphan*/  ipv6_prefixes_cnt; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* sk_dst_get (int /*<<< orphan*/ ) ; 
 int smc_clc_prfx_match4_rcu (int /*<<< orphan*/ ,struct smc_clc_msg_proposal_prefix*) ; 
 int smc_clc_prfx_match6_rcu (int /*<<< orphan*/ ,struct smc_clc_msg_proposal_prefix*) ; 

int smc_clc_prfx_match(struct socket *clcsock,
		       struct smc_clc_msg_proposal_prefix *prop)
{
	struct dst_entry *dst = sk_dst_get(clcsock->sk);
	int rc;

	if (!dst) {
		rc = -ENOTCONN;
		goto out;
	}
	if (!dst->dev) {
		rc = -ENODEV;
		goto out_rel;
	}
	rcu_read_lock();
	if (!prop->ipv6_prefixes_cnt)
		rc = smc_clc_prfx_match4_rcu(dst->dev, prop);
	else
		rc = smc_clc_prfx_match6_rcu(dst->dev, prop);
	rcu_read_unlock();
out_rel:
	dst_release(dst);
out:
	return rc;
}