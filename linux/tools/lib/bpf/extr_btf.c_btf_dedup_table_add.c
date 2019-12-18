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
struct btf_dedup {int /*<<< orphan*/  dedup_table; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int hashmap__append (int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static int btf_dedup_table_add(struct btf_dedup *d, long hash, __u32 type_id)
{
	return hashmap__append(d->dedup_table,
			       (void *)hash, (void *)(long)type_id);
}