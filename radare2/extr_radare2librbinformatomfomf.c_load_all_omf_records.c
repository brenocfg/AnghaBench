#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {TYPE_2__* records; } ;
typedef  TYPE_1__ r_bin_omf_obj ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ OMF_record_handler ;
typedef  TYPE_3__ OMF_record ;

/* Variables and functions */
 TYPE_2__* load_record_omf (int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int load_all_omf_records(r_bin_omf_obj *obj, const ut8 *buf, ut64 size) {
	ut64 ct = 0;
	OMF_record_handler *new_rec = NULL;
	OMF_record_handler *tmp = NULL;

	while (ct < size) {
		if (!(new_rec = load_record_omf (buf + ct, ct, size - ct))) {
			return false;
		}

		// the order is important because some link are made by index
		if (!tmp) {
			obj->records = new_rec;
			tmp = obj->records;
		} else {
			tmp->next = new_rec;
			tmp = tmp->next;
		}
		ct += 3 + ((OMF_record *)tmp)->size;
	}
	return true;
}