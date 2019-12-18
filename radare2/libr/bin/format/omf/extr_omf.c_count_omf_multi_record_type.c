#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_6__ {TYPE_2__* records; } ;
typedef  TYPE_1__ r_bin_omf_obj ;
struct TYPE_9__ {scalar_t__ nb_elem; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ content; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ OMF_record_handler ;
typedef  TYPE_3__ OMF_record ;
typedef  TYPE_4__ OMF_multi_datas ;

/* Variables and functions */

__attribute__((used)) static ut32 count_omf_multi_record_type(r_bin_omf_obj *obj, ut8 type) {
	OMF_record_handler *tmp = obj->records;
	ut32 ct = 0;

	while (tmp) {
		if (((OMF_record *)tmp)->type == type) {
			ct += ((OMF_multi_datas *)((OMF_record *)tmp)->content)->nb_elem;
		}
		tmp = tmp->next;
	}
	return ct;
}