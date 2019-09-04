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
struct TYPE_6__ {TYPE_2__* records; } ;
typedef  TYPE_1__ r_bin_omf_obj ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__* content; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ OMF_record_handler ;
typedef  TYPE_3__ OMF_record ;
typedef  int /*<<< orphan*/  OMF_multi_datas ;

/* Variables and functions */
 scalar_t__ OMF_LNAMES ; 
 scalar_t__ OMF_PUBDEF ; 
 int /*<<< orphan*/  R_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  free_lname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pubdef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_all_omf_records(r_bin_omf_obj *obj) {
	OMF_record_handler *tmp = NULL;
	OMF_record_handler *rec = obj->records;

	while (rec) {
		if (((OMF_record *)rec)->type == OMF_LNAMES) {
			free_lname((OMF_multi_datas *)((OMF_record *)rec)->content);
		} else if (((OMF_record *)rec)->type == OMF_PUBDEF) {
			free_pubdef((OMF_multi_datas *)((OMF_record *)rec)->content);
		} else {
			R_FREE (((OMF_record *)rec)->content);
		}
		tmp = rec->next;
		R_FREE(rec);
		rec = tmp;
	}
	obj->records = NULL;
}