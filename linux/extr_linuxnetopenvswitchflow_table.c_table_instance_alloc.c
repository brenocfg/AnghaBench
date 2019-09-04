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
struct table_instance {int n_buckets; int keep_flows; int /*<<< orphan*/  hash_seed; scalar_t__ node_ver; int /*<<< orphan*/  buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_buckets (int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct table_instance*) ; 
 struct table_instance* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct table_instance *table_instance_alloc(int new_size)
{
	struct table_instance *ti = kmalloc(sizeof(*ti), GFP_KERNEL);

	if (!ti)
		return NULL;

	ti->buckets = alloc_buckets(new_size);

	if (!ti->buckets) {
		kfree(ti);
		return NULL;
	}
	ti->n_buckets = new_size;
	ti->node_ver = 0;
	ti->keep_flows = false;
	get_random_bytes(&ti->hash_seed, sizeof(u32));

	return ti;
}