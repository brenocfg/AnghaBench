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
typedef  int /*<<< orphan*/  u64 ;
struct sym_data {int /*<<< orphan*/  node; int /*<<< orphan*/  addr; } ;
struct kcore_copy_info {int /*<<< orphan*/  syms; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sym_data* zalloc (int) ; 

__attribute__((used)) static struct sym_data *kcore_copy__new_sym(struct kcore_copy_info *kci,
					    u64 addr)
{
	struct sym_data *s = zalloc(sizeof(*s));

	if (s) {
		s->addr = addr;
		list_add_tail(&s->node, &kci->syms);
	}

	return s;
}