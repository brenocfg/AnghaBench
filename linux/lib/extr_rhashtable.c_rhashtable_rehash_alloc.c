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
struct bucket_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RHT_MUTEX (struct rhashtable*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bucket_table* bucket_table_alloc (struct rhashtable*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucket_table_free (struct bucket_table*) ; 
 int rhashtable_rehash_attach (struct rhashtable*,struct bucket_table*,struct bucket_table*) ; 

__attribute__((used)) static int rhashtable_rehash_alloc(struct rhashtable *ht,
				   struct bucket_table *old_tbl,
				   unsigned int size)
{
	struct bucket_table *new_tbl;
	int err;

	ASSERT_RHT_MUTEX(ht);

	new_tbl = bucket_table_alloc(ht, size, GFP_KERNEL);
	if (new_tbl == NULL)
		return -ENOMEM;

	err = rhashtable_rehash_attach(ht, old_tbl, new_tbl);
	if (err)
		bucket_table_free(new_tbl);

	return err;
}