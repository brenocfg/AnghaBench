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
struct nsm_handle {int /*<<< orphan*/  sm_count; int /*<<< orphan*/  sm_addrbuf; int /*<<< orphan*/  sm_name; } ;
struct nlm_reboot {int /*<<< orphan*/  mon; int /*<<< orphan*/  len; int /*<<< orphan*/  priv; } ;
struct net {int dummy; } ;
struct lockd_net {int /*<<< orphan*/  nsm_handles; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lockd_net_id ; 
 struct lockd_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsm_lock ; 
 struct nsm_handle* nsm_lookup_priv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct nsm_handle *nsm_reboot_lookup(const struct net *net,
				const struct nlm_reboot *info)
{
	struct nsm_handle *cached;
	struct lockd_net *ln = net_generic(net, lockd_net_id);

	spin_lock(&nsm_lock);

	cached = nsm_lookup_priv(&ln->nsm_handles, &info->priv);
	if (unlikely(cached == NULL)) {
		spin_unlock(&nsm_lock);
		dprintk("lockd: never saw rebooted peer '%.*s' before\n",
				info->len, info->mon);
		return cached;
	}

	refcount_inc(&cached->sm_count);
	spin_unlock(&nsm_lock);

	dprintk("lockd: host %s (%s) rebooted, cnt %d\n",
			cached->sm_name, cached->sm_addrbuf,
			refcount_read(&cached->sm_count));
	return cached;
}