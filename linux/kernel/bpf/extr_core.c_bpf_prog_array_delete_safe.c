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
struct TYPE_2__ {int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (struct bpf_prog*,int /*<<< orphan*/ *) ; 
 TYPE_1__ dummy_bpf_prog ; 

void bpf_prog_array_delete_safe(struct bpf_prog_array *array,
				struct bpf_prog *old_prog)
{
	struct bpf_prog_array_item *item;

	for (item = array->items; item->prog; item++)
		if (item->prog == old_prog) {
			WRITE_ONCE(item->prog, &dummy_bpf_prog.prog);
			break;
		}
}