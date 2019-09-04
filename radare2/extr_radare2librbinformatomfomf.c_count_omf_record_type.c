#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut8 ;
typedef  scalar_t__ ut32 ;
struct TYPE_5__ {TYPE_2__* records; } ;
typedef  TYPE_1__ r_bin_omf_obj ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ OMF_record_handler ;
typedef  TYPE_3__ OMF_record ;

/* Variables and functions */

__attribute__((used)) static ut32 count_omf_record_type(r_bin_omf_obj *obj, ut8 type) {
	OMF_record_handler *tmp = obj->records;
	ut32 ct = 0;

	while (tmp) {
		if (((OMF_record *)tmp)->type == type) {
			ct++;
		}
		tmp = tmp->next;
	}
	return ct;
}