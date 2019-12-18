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
typedef  int u32 ;
struct table_instance {int n_buckets; struct hlist_head* buckets; int /*<<< orphan*/  hash_seed; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int jhash_1word (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *find_bucket(struct table_instance *ti, u32 hash)
{
	hash = jhash_1word(hash, ti->hash_seed);
	return &ti->buckets[hash & (ti->n_buckets - 1)];
}