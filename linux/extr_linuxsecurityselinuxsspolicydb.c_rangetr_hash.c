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
struct range_trans {int source_type; int target_type; int target_class; } ;
struct hashtab {int size; } ;

/* Variables and functions */

__attribute__((used)) static u32 rangetr_hash(struct hashtab *h, const void *k)
{
	const struct range_trans *key = k;
	return (key->source_type + (key->target_type << 3) +
		(key->target_class << 5)) & (h->size - 1);
}