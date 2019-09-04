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
struct type_datum {scalar_t__ value; scalar_t__ attribute; scalar_t__ bounds; } ;
struct policydb {int /*<<< orphan*/  type_val_to_struct_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int POLICYDB_BOUNDS_MAXDEPTH ; 
 int /*<<< orphan*/  SYM_TYPES ; 
 struct type_datum* flex_array_get_ptr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,char*,...) ; 
 int /*<<< orphan*/  sym_name (struct policydb*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int type_bounds_sanity_check(void *key, void *datum, void *datap)
{
	struct type_datum *upper;
	struct policydb *p = datap;
	int depth = 0;

	upper = datum;
	while (upper->bounds) {
		if (++depth == POLICYDB_BOUNDS_MAXDEPTH) {
			pr_err("SELinux: type %s: "
			       "too deep or looped boundary\n",
			       (char *) key);
			return -EINVAL;
		}

		upper = flex_array_get_ptr(p->type_val_to_struct_array,
					   upper->bounds - 1);
		BUG_ON(!upper);

		if (upper->attribute) {
			pr_err("SELinux: type %s: "
			       "bounded by attribute %s",
			       (char *) key,
			       sym_name(p, SYM_TYPES, upper->value - 1));
			return -EINVAL;
		}
	}

	return 0;
}