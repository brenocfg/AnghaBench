#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_section; TYPE_2__** sections; TYPE_3__* records; } ;
typedef  TYPE_1__ r_bin_omf_obj ;
struct TYPE_13__ {int seg_idx; struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_5__* content; } ;
struct TYPE_11__ {struct TYPE_11__* next; } ;
struct TYPE_10__ {TYPE_5__* data; } ;
typedef  TYPE_2__ OMF_segment ;
typedef  TYPE_3__ OMF_record_handler ;
typedef  TYPE_4__ OMF_record ;
typedef  TYPE_5__ OMF_data ;

/* Variables and functions */
 int /*<<< orphan*/  OMF_LEDATA ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_3__* get_next_omf_record_type (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_omf_data_info(r_bin_omf_obj *obj) {
	OMF_record_handler *tmp = obj->records;
	OMF_data *tmp_data;

	while ((tmp = get_next_omf_record_type (tmp, OMF_LEDATA))) {
		if (((OMF_data *)((OMF_record *)tmp)->content)->seg_idx - 1 >= obj->nb_section) {
			eprintf ("Invalid Ledata record (bad segment index)\n");
			return false;
		}
		OMF_segment *os = obj->sections[((OMF_data *)((OMF_record *)tmp)->content)->seg_idx - 1];
		if (os && (tmp_data = os->data)) {
			while (tmp_data->next) {
				tmp_data = tmp_data->next;
			}
			tmp_data->next = ((OMF_record *)tmp)->content;
		} else {
			obj->sections[((OMF_data *)((OMF_record *)tmp)->content)->seg_idx - 1]->data = ((OMF_record *)tmp)->content;
		}
		((OMF_record *)tmp)->content = NULL;
		tmp = tmp->next;
	}
	return true;
}