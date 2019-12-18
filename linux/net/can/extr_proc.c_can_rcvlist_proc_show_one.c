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
struct seq_file {int dummy; } ;
struct net_device {int dummy; } ;
struct can_dev_rcv_lists {int /*<<< orphan*/ * rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNAME (struct net_device*) ; 
 int /*<<< orphan*/  can_print_rcvlist (struct seq_file*,int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  can_print_recv_banner (struct seq_file*) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void can_rcvlist_proc_show_one(struct seq_file *m, int idx,
					     struct net_device *dev,
					     struct can_dev_rcv_lists *dev_rcv_lists)
{
	if (!hlist_empty(&dev_rcv_lists->rx[idx])) {
		can_print_recv_banner(m);
		can_print_rcvlist(m, &dev_rcv_lists->rx[idx], dev);
	} else
		seq_printf(m, "  (%s: no entry)\n", DNAME(dev));

}