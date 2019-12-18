#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog_array_item {struct bpf_prog* prog; } ;
struct bpf_prog_array {struct bpf_prog_array_item* items; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_2__ {struct bpf_prog prog; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bpf_prog_array* bpf_prog_array_alloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ dummy_bpf_prog ; 

int bpf_prog_array_copy(struct bpf_prog_array *old_array,
			struct bpf_prog *exclude_prog,
			struct bpf_prog *include_prog,
			struct bpf_prog_array **new_array)
{
	int new_prog_cnt, carry_prog_cnt = 0;
	struct bpf_prog_array_item *existing;
	struct bpf_prog_array *array;
	bool found_exclude = false;
	int new_prog_idx = 0;

	/* Figure out how many existing progs we need to carry over to
	 * the new array.
	 */
	if (old_array) {
		existing = old_array->items;
		for (; existing->prog; existing++) {
			if (existing->prog == exclude_prog) {
				found_exclude = true;
				continue;
			}
			if (existing->prog != &dummy_bpf_prog.prog)
				carry_prog_cnt++;
			if (existing->prog == include_prog)
				return -EEXIST;
		}
	}

	if (exclude_prog && !found_exclude)
		return -ENOENT;

	/* How many progs (not NULL) will be in the new array? */
	new_prog_cnt = carry_prog_cnt;
	if (include_prog)
		new_prog_cnt += 1;

	/* Do we have any prog (not NULL) in the new array? */
	if (!new_prog_cnt) {
		*new_array = NULL;
		return 0;
	}

	/* +1 as the end of prog_array is marked with NULL */
	array = bpf_prog_array_alloc(new_prog_cnt + 1, GFP_KERNEL);
	if (!array)
		return -ENOMEM;

	/* Fill in the new prog array */
	if (carry_prog_cnt) {
		existing = old_array->items;
		for (; existing->prog; existing++)
			if (existing->prog != exclude_prog &&
			    existing->prog != &dummy_bpf_prog.prog) {
				array->items[new_prog_idx++].prog =
					existing->prog;
			}
	}
	if (include_prog)
		array->items[new_prog_idx++].prog = include_prog;
	array->items[new_prog_idx].prog = NULL;
	*new_array = array;
	return 0;
}