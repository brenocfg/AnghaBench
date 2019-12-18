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
struct rhashtable {int dummy; } ;
struct bucket_table {int /*<<< orphan*/  future_tbl; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/ * cmpxchg (struct bucket_table**,int /*<<< orphan*/ *,struct bucket_table*) ; 

__attribute__((used)) static int rhashtable_rehash_attach(struct rhashtable *ht,
				    struct bucket_table *old_tbl,
				    struct bucket_table *new_tbl)
{
	/* Make insertions go into the new, empty table right away. Deletions
	 * and lookups will be attempted in both tables until we synchronize.
	 * As cmpxchg() provides strong barriers, we do not need
	 * rcu_assign_pointer().
	 */

	if (cmpxchg((struct bucket_table **)&old_tbl->future_tbl, NULL,
		    new_tbl) != NULL)
		return -EEXIST;

	return 0;
}