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
typedef  size_t u8 ;
struct sw842_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t OPS_MAX ; 
 size_t OP_ACTION ; 
#define  OP_ACTION_DATA 130 
#define  OP_ACTION_INDEX 129 
#define  OP_ACTION_NOOP 128 
 size_t OP_AMOUNT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t** decomp_ops ; 
 int do_data (struct sw842_param*,size_t) ; 
 int do_index (struct sw842_param*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 scalar_t__ sw842_template_counts ; 
 int /*<<< orphan*/ * template_count ; 

__attribute__((used)) static int do_op(struct sw842_param *p, u8 o)
{
	int i, ret = 0;

	if (o >= OPS_MAX)
		return -EINVAL;

	for (i = 0; i < 4; i++) {
		u8 op = decomp_ops[o][i];

		pr_debug("op is %x\n", op);

		switch (op & OP_ACTION) {
		case OP_ACTION_DATA:
			ret = do_data(p, op & OP_AMOUNT);
			break;
		case OP_ACTION_INDEX:
			ret = do_index(p, op & OP_AMOUNT);
			break;
		case OP_ACTION_NOOP:
			break;
		default:
			pr_err("Internal error, invalid op %x\n", op);
			return -EINVAL;
		}

		if (ret)
			return ret;
	}

	if (sw842_template_counts)
		atomic_inc(&template_count[o]);

	return 0;
}