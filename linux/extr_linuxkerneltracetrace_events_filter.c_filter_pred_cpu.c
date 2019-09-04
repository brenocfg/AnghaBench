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
struct filter_pred {int val; int op; } ;

/* Variables and functions */
#define  OP_EQ 133 
#define  OP_GE 132 
#define  OP_GT 131 
#define  OP_LE 130 
#define  OP_LT 129 
#define  OP_NE 128 
 int raw_smp_processor_id () ; 

__attribute__((used)) static int filter_pred_cpu(struct filter_pred *pred, void *event)
{
	int cpu, cmp;

	cpu = raw_smp_processor_id();
	cmp = pred->val;

	switch (pred->op) {
	case OP_EQ:
		return cpu == cmp;
	case OP_NE:
		return cpu != cmp;
	case OP_LT:
		return cpu < cmp;
	case OP_LE:
		return cpu <= cmp;
	case OP_GT:
		return cpu > cmp;
	case OP_GE:
		return cpu >= cmp;
	default:
		return 0;
	}
}