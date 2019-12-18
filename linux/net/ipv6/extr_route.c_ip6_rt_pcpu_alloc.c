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
struct rt6_info {int /*<<< orphan*/  rt6i_flags; } ;
struct net_device {int dummy; } ;
struct fib6_result {struct fib6_info* f6i; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_PCPU ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 unsigned short fib6_info_dst_flags (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_info_hold_safe (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 struct rt6_info* ip6_dst_alloc (int /*<<< orphan*/ ,struct net_device*,unsigned short) ; 
 int /*<<< orphan*/  ip6_rt_copy_init (struct rt6_info*,struct fib6_result const*) ; 
 struct net_device* ip6_rt_get_dev_rcu (struct fib6_result const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct rt6_info *ip6_rt_pcpu_alloc(const struct fib6_result *res)
{
	struct fib6_info *f6i = res->f6i;
	unsigned short flags = fib6_info_dst_flags(f6i);
	struct net_device *dev;
	struct rt6_info *pcpu_rt;

	if (!fib6_info_hold_safe(f6i))
		return NULL;

	rcu_read_lock();
	dev = ip6_rt_get_dev_rcu(res);
	pcpu_rt = ip6_dst_alloc(dev_net(dev), dev, flags);
	rcu_read_unlock();
	if (!pcpu_rt) {
		fib6_info_release(f6i);
		return NULL;
	}
	ip6_rt_copy_init(pcpu_rt, res);
	pcpu_rt->rt6i_flags |= RTF_PCPU;
	return pcpu_rt;
}