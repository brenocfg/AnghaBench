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
struct rhashtable {int /*<<< orphan*/  p; } ;
struct rhash_head {int dummy; } ;
struct bucket_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rht_head_hashfn (struct rhashtable*,struct bucket_table const*,struct rhash_head const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 head_hashfn(struct rhashtable *ht,
		       const struct bucket_table *tbl,
		       const struct rhash_head *he)
{
	return rht_head_hashfn(ht, tbl, he, ht->p);
}