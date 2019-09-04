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
struct nf_flowtable {int /*<<< orphan*/  gc_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_flow_table_do_cleanup ; 
 int /*<<< orphan*/  nf_flow_table_iterate (struct nf_flowtable*,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static void nf_flow_table_iterate_cleanup(struct nf_flowtable *flowtable,
					  struct net_device *dev)
{
	nf_flow_table_iterate(flowtable, nf_flow_table_do_cleanup, dev);
	flush_delayed_work(&flowtable->gc_work);
}