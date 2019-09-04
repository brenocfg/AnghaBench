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
typedef  scalar_t__ u32 ;
struct stack_record {scalar_t__ hash; int size; int /*<<< orphan*/  entries; struct stack_record* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  stackdepot_memcmp (unsigned long*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct stack_record *find_stack(struct stack_record *bucket,
					     unsigned long *entries, int size,
					     u32 hash)
{
	struct stack_record *found;

	for (found = bucket; found; found = found->next) {
		if (found->hash == hash &&
		    found->size == size &&
		    !stackdepot_memcmp(entries, found->entries, size))
			return found;
	}
	return NULL;
}