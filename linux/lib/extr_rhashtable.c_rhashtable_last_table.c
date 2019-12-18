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
 struct bucket_table* rht_dereference_rcu (int /*<<< orphan*/ ,struct rhashtable*) ; 

__attribute__((used)) static struct bucket_table *rhashtable_last_table(struct rhashtable *ht,
						  struct bucket_table *tbl)
{
	struct bucket_table *new_tbl;

	do {
		new_tbl = tbl;
		tbl = rht_dereference_rcu(tbl->future_tbl, ht);
	} while (tbl);

	return new_tbl;
}