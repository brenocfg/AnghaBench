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
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct bpf_map_op {scalar_t__ key_type; TYPE_1__ k; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_KEY_RANGES ; 
 int /*<<< orphan*/  free (struct bpf_map_op*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_events__clear_array (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bpf_map_op__delete(struct bpf_map_op *op)
{
	if (!list_empty(&op->list))
		list_del_init(&op->list);
	if (op->key_type == BPF_MAP_KEY_RANGES)
		parse_events__clear_array(&op->k.array);
	free(op);
}