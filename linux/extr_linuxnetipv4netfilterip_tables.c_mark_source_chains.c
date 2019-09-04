#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xt_table_info {unsigned int* hook_entry; unsigned int size; int /*<<< orphan*/  number; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ user; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct xt_standard_target {int verdict; TYPE_3__ target; } ;
struct TYPE_8__ {unsigned int pcnt; } ;
struct ipt_entry {int comefrom; unsigned int next_offset; TYPE_4__ counters; } ;

/* Variables and functions */
 unsigned int NF_INET_NUMHOOKS ; 
 int /*<<< orphan*/  XT_STANDARD_TARGET ; 
 scalar_t__ ipt_get_target_c (struct ipt_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unconditional (struct ipt_entry*) ; 
 int /*<<< orphan*/  xt_find_jump_offset (unsigned int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mark_source_chains(const struct xt_table_info *newinfo,
		   unsigned int valid_hooks, void *entry0,
		   unsigned int *offsets)
{
	unsigned int hook;

	/* No recursion; use packet counter to save back ptrs (reset
	   to 0 as we leave), and comefrom to save source hook bitmask */
	for (hook = 0; hook < NF_INET_NUMHOOKS; hook++) {
		unsigned int pos = newinfo->hook_entry[hook];
		struct ipt_entry *e = entry0 + pos;

		if (!(valid_hooks & (1 << hook)))
			continue;

		/* Set initial back pointer. */
		e->counters.pcnt = pos;

		for (;;) {
			const struct xt_standard_target *t
				= (void *)ipt_get_target_c(e);
			int visited = e->comefrom & (1 << hook);

			if (e->comefrom & (1 << NF_INET_NUMHOOKS))
				return 0;

			e->comefrom |= ((1 << hook) | (1 << NF_INET_NUMHOOKS));

			/* Unconditional return/END. */
			if ((unconditional(e) &&
			     (strcmp(t->target.u.user.name,
				     XT_STANDARD_TARGET) == 0) &&
			     t->verdict < 0) || visited) {
				unsigned int oldpos, size;

				/* Return: backtrack through the last
				   big jump. */
				do {
					e->comefrom ^= (1<<NF_INET_NUMHOOKS);
					oldpos = pos;
					pos = e->counters.pcnt;
					e->counters.pcnt = 0;

					/* We're at the start. */
					if (pos == oldpos)
						goto next;

					e = entry0 + pos;
				} while (oldpos == pos + e->next_offset);

				/* Move along one */
				size = e->next_offset;
				e = entry0 + pos + size;
				if (pos + size >= newinfo->size)
					return 0;
				e->counters.pcnt = pos;
				pos += size;
			} else {
				int newpos = t->verdict;

				if (strcmp(t->target.u.user.name,
					   XT_STANDARD_TARGET) == 0 &&
				    newpos >= 0) {
					/* This a jump; chase it. */
					if (!xt_find_jump_offset(offsets, newpos,
								 newinfo->number))
						return 0;
				} else {
					/* ... this is a fallthru */
					newpos = pos + e->next_offset;
					if (newpos >= newinfo->size)
						return 0;
				}
				e = entry0 + newpos;
				e->counters.pcnt = pos;
				pos = newpos;
			}
		}
next:		;
	}
	return 1;
}