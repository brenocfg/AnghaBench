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
struct TYPE_4__ {int base_type; } ;
struct TYPE_3__ {scalar_t__ type_info; } ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SLF_BITFIELD ;

/* Variables and functions */
 int base_idx ; 
 int /*<<< orphan*/  p_types_list ; 
 void* r_list_get_n (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_bitfield_base_type(void *type, void **ret_type) {
	STypeInfo *t = (STypeInfo *) type;
	SLF_BITFIELD *lf = (SLF_BITFIELD *) t->type_info;
	int curr_idx = lf->base_type;

	if (curr_idx < base_idx) {
		*ret_type = 0;
	} else {
		curr_idx -= base_idx;
		*ret_type = r_list_get_n(p_types_list, curr_idx);
	}

	return curr_idx;
}