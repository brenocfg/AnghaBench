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
struct tun_struct {int /*<<< orphan*/  filter_prog; int /*<<< orphan*/  steering_prog; int /*<<< orphan*/  security; int /*<<< orphan*/  pcpu_stats; int /*<<< orphan*/  disabled; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __tun_set_ebpf (struct tun_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  security_tun_dev_free_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_flow_uninit (struct tun_struct*) ; 

__attribute__((used)) static void tun_free_netdev(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	BUG_ON(!(list_empty(&tun->disabled)));
	free_percpu(tun->pcpu_stats);
	tun_flow_uninit(tun);
	security_tun_dev_free_security(tun->security);
	__tun_set_ebpf(tun, &tun->steering_prog, NULL);
	__tun_set_ebpf(tun, &tun->filter_prog, NULL);
}