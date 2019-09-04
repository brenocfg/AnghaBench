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
typedef  scalar_t__ ut32 ;
struct TYPE_7__ {scalar_t__ nb_section; int /*<<< orphan*/ * sections; } ;
typedef  TYPE_2__ r_bin_omf_obj ;
struct TYPE_8__ {TYPE_1__* o; } ;
struct TYPE_6__ {TYPE_2__* bin_obj; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  r_bin_omf_send_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * r_list_new () ; 

__attribute__((used)) static RList *sections(RBinFile *bf) {
	RList *ret;
	ut32 ct_omf_sect = 0;

	if (!bf || !bf->o || !bf->o->bin_obj) {
		return NULL;
	}
	r_bin_omf_obj *obj = bf->o->bin_obj;

	if (!(ret = r_list_new ())) {
		return NULL;
	}

	while (ct_omf_sect < obj->nb_section) {
		if (!r_bin_omf_send_sections (ret,\
			    obj->sections[ct_omf_sect++], bf->o->bin_obj)) {
			return ret;
		}
	}
	return ret;
}