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
struct gcov_info {unsigned int n_functions; TYPE_1__** functions; } ;
struct gcov_ctr_info {unsigned int num; scalar_t__* values; } ;
struct TYPE_2__ {struct gcov_ctr_info* ctrs; } ;

/* Variables and functions */
 unsigned int GCOV_COUNTERS ; 
 int /*<<< orphan*/  counter_active (struct gcov_info*,unsigned int) ; 

void gcov_info_add(struct gcov_info *dst, struct gcov_info *src)
{
	struct gcov_ctr_info *dci_ptr;
	struct gcov_ctr_info *sci_ptr;
	unsigned int fi_idx;
	unsigned int ct_idx;
	unsigned int val_idx;

	for (fi_idx = 0; fi_idx < src->n_functions; fi_idx++) {
		dci_ptr = dst->functions[fi_idx]->ctrs;
		sci_ptr = src->functions[fi_idx]->ctrs;

		for (ct_idx = 0; ct_idx < GCOV_COUNTERS; ct_idx++) {
			if (!counter_active(src, ct_idx))
				continue;

			for (val_idx = 0; val_idx < sci_ptr->num; val_idx++)
				dci_ptr->values[val_idx] +=
					sci_ptr->values[val_idx];

			dci_ptr++;
			sci_ptr++;
		}
	}
}