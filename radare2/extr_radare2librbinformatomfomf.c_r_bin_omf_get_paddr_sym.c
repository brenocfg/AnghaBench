#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  long long ut64 ;
struct TYPE_8__ {int nb_section; TYPE_1__** sections; } ;
typedef  TYPE_2__ r_bin_omf_obj ;
struct TYPE_10__ {long long size; long long offset; long long paddr; struct TYPE_10__* next; } ;
struct TYPE_9__ {int seg_idx; long long offset; } ;
struct TYPE_7__ {TYPE_4__* data; } ;
typedef  TYPE_3__ OMF_symbol ;
typedef  TYPE_4__ OMF_data ;

/* Variables and functions */

ut64 r_bin_omf_get_paddr_sym(r_bin_omf_obj *obj, OMF_symbol *sym) {
	ut64 offset = 0;
	if (!obj->sections) {
		return 0LL;
	}
	if (sym->seg_idx - 1 > obj->nb_section) {
		return 0LL;
	}
	int sidx = sym->seg_idx - 1;
	if (sidx >= obj->nb_section) {
		return 0LL;
	}
	OMF_data *data = obj->sections[sidx]->data;
	while (data) {
		offset += data->size;
		if (sym->offset < offset) {
			return sym->offset - data->offset + data->paddr;
		}
		data = data->next;
	}
	return 0;
}