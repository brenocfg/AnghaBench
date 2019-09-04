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
struct rtentry {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct fib_table {int dummy; } ;
struct fib_config {int /*<<< orphan*/  fc_mx; int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int EPERM ; 
 int ESRCH ; 
#define  SIOCADDRT 129 
#define  SIOCDELRT 128 
 struct fib_table* fib_get_table (struct net*,int /*<<< orphan*/ ) ; 
 struct fib_table* fib_new_table (struct net*,int /*<<< orphan*/ ) ; 
 int fib_table_delete (struct net*,struct fib_table*,struct fib_config*,int /*<<< orphan*/ *) ; 
 int fib_table_insert (struct net*,struct fib_table*,struct fib_config*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtentry_to_fib_config (struct net*,unsigned int,struct rtentry*,struct fib_config*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int ip_rt_ioctl(struct net *net, unsigned int cmd, struct rtentry *rt)
{
	struct fib_config cfg;
	int err;

	switch (cmd) {
	case SIOCADDRT:		/* Add a route */
	case SIOCDELRT:		/* Delete a route */
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			return -EPERM;

		rtnl_lock();
		err = rtentry_to_fib_config(net, cmd, rt, &cfg);
		if (err == 0) {
			struct fib_table *tb;

			if (cmd == SIOCDELRT) {
				tb = fib_get_table(net, cfg.fc_table);
				if (tb)
					err = fib_table_delete(net, tb, &cfg,
							       NULL);
				else
					err = -ESRCH;
			} else {
				tb = fib_new_table(net, cfg.fc_table);
				if (tb)
					err = fib_table_insert(net, tb,
							       &cfg, NULL);
				else
					err = -ENOBUFS;
			}

			/* allocated by rtentry_to_fib_config() */
			kfree(cfg.fc_mx);
		}
		rtnl_unlock();
		return err;
	}
	return -EINVAL;
}