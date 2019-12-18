#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size_log2; TYPE_1__* control; int /*<<< orphan*/  area; int /*<<< orphan*/  buckets; } ;
typedef  TYPE_2__ dshash_table ;
struct TYPE_4__ {scalar_t__ size_log2; int /*<<< orphan*/  buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ensure_valid_bucket_pointers(dshash_table *hash_table)
{
	if (hash_table->size_log2 != hash_table->control->size_log2)
	{
		hash_table->buckets = dsa_get_address(hash_table->area,
											  hash_table->control->buckets);
		hash_table->size_log2 = hash_table->control->size_log2;
	}
}