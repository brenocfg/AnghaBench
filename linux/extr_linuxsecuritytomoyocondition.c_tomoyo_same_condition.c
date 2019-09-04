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
struct tomoyo_condition {scalar_t__ size; scalar_t__ condc; scalar_t__ numbers_count; scalar_t__ names_count; scalar_t__ argc; scalar_t__ envc; scalar_t__ grant_log; scalar_t__ transit; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (struct tomoyo_condition const*,struct tomoyo_condition const*,scalar_t__) ; 

__attribute__((used)) static inline bool tomoyo_same_condition(const struct tomoyo_condition *a,
					 const struct tomoyo_condition *b)
{
	return a->size == b->size && a->condc == b->condc &&
		a->numbers_count == b->numbers_count &&
		a->names_count == b->names_count &&
		a->argc == b->argc && a->envc == b->envc &&
		a->grant_log == b->grant_log && a->transit == b->transit &&
		!memcmp(a + 1, b + 1, a->size - sizeof(*a));
}