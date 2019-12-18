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
struct parse_events_term {int dummy; } ;
struct bpf_map_op {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct bpf_map_op* ERR_PTR (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int bpf_map_op_setkey (struct bpf_map_op*,struct parse_events_term*) ; 
 int /*<<< orphan*/  free (struct bpf_map_op*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct bpf_map_op* zalloc (int) ; 

__attribute__((used)) static struct bpf_map_op *
bpf_map_op__new(struct parse_events_term *term)
{
	struct bpf_map_op *op;
	int err;

	op = zalloc(sizeof(*op));
	if (!op) {
		pr_debug("Failed to alloc bpf_map_op\n");
		return ERR_PTR(-ENOMEM);
	}
	INIT_LIST_HEAD(&op->list);

	err = bpf_map_op_setkey(op, term);
	if (err) {
		free(op);
		return ERR_PTR(err);
	}
	return op;
}