#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nr_ranges; struct bpf_map_op* ranges; } ;
struct TYPE_4__ {TYPE_1__ array; } ;
struct bpf_map_op {scalar_t__ key_type; TYPE_2__ k; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_KEY_RANGES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct bpf_map_op*) ; 
 void* memdup (struct bpf_map_op*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static struct bpf_map_op *
bpf_map_op__clone(struct bpf_map_op *op)
{
	struct bpf_map_op *newop;

	newop = memdup(op, sizeof(*op));
	if (!newop) {
		pr_debug("Failed to alloc bpf_map_op\n");
		return NULL;
	}

	INIT_LIST_HEAD(&newop->list);
	if (op->key_type == BPF_MAP_KEY_RANGES) {
		size_t memsz = op->k.array.nr_ranges *
			       sizeof(op->k.array.ranges[0]);

		newop->k.array.ranges = memdup(op->k.array.ranges, memsz);
		if (!newop->k.array.ranges) {
			pr_debug("Failed to alloc indices for map\n");
			free(newop);
			return NULL;
		}
	}

	return newop;
}