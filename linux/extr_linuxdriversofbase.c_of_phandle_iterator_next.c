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
typedef  scalar_t__ uint32_t ;
struct of_phandle_iterator {scalar_t__ cur; scalar_t__ phandle_end; scalar_t__ list_end; scalar_t__ cell_count; int /*<<< orphan*/ * node; scalar_t__ cur_count; int /*<<< orphan*/  parent; scalar_t__ cells_name; scalar_t__ phandle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_find_node_by_phandle (scalar_t__) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

int of_phandle_iterator_next(struct of_phandle_iterator *it)
{
	uint32_t count = 0;

	if (it->node) {
		of_node_put(it->node);
		it->node = NULL;
	}

	if (!it->cur || it->phandle_end >= it->list_end)
		return -ENOENT;

	it->cur = it->phandle_end;

	/* If phandle is 0, then it is an empty entry with no arguments. */
	it->phandle = be32_to_cpup(it->cur++);

	if (it->phandle) {

		/*
		 * Find the provider node and parse the #*-cells property to
		 * determine the argument length.
		 */
		it->node = of_find_node_by_phandle(it->phandle);

		if (it->cells_name) {
			if (!it->node) {
				pr_err("%pOF: could not find phandle\n",
				       it->parent);
				goto err;
			}

			if (of_property_read_u32(it->node, it->cells_name,
						 &count)) {
				pr_err("%pOF: could not get %s for %pOF\n",
				       it->parent,
				       it->cells_name,
				       it->node);
				goto err;
			}
		} else {
			count = it->cell_count;
		}

		/*
		 * Make sure that the arguments actually fit in the remaining
		 * property data length
		 */
		if (it->cur + count > it->list_end) {
			pr_err("%pOF: arguments longer than property\n",
			       it->parent);
			goto err;
		}
	}

	it->phandle_end = it->cur + count;
	it->cur_count = count;

	return 0;

err:
	if (it->node) {
		of_node_put(it->node);
		it->node = NULL;
	}

	return -EINVAL;
}