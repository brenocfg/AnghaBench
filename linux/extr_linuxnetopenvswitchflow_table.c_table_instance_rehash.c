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
struct table_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_table_copy_flows (struct table_instance*,struct table_instance*,int) ; 
 struct table_instance* table_instance_alloc (int) ; 

__attribute__((used)) static struct table_instance *table_instance_rehash(struct table_instance *ti,
						    int n_buckets, bool ufid)
{
	struct table_instance *new_ti;

	new_ti = table_instance_alloc(n_buckets);
	if (!new_ti)
		return NULL;

	flow_table_copy_flows(ti, new_ti, ufid);

	return new_ti;
}