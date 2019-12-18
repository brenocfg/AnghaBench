#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ ** names; TYPE_2__* records; } ;
typedef  TYPE_1__ r_bin_omf_obj ;
struct TYPE_11__ {int nb_elem; scalar_t__ elems; } ;
struct TYPE_10__ {scalar_t__ content; } ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ OMF_record_handler ;
typedef  TYPE_3__ OMF_record ;
typedef  TYPE_4__ OMF_multi_datas ;

/* Variables and functions */
 int /*<<< orphan*/  OMF_LNAMES ; 
 TYPE_2__* get_next_omf_record_type (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static int cpy_omf_names(r_bin_omf_obj *obj) {
	OMF_record_handler *tmp = obj->records;
	OMF_multi_datas	*lname;
	int ct_obj = 0;
	int ct_rec;

	while ((tmp = get_next_omf_record_type(tmp, OMF_LNAMES))) {
		lname = (OMF_multi_datas *)((OMF_record *)tmp)->content;

		ct_rec = -1;
		while (++ct_rec < lname->nb_elem) {
			if (!((char **)lname->elems)[ct_rec]) {
				obj->names[ct_obj++] = NULL;
			} else if (!(obj->names[ct_obj++] = strdup(((char **)lname->elems)[ct_rec]))) {
				return false;
			}
		}
		tmp = tmp->next;
	}
	return true;
}