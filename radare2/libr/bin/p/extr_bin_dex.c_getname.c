#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r_bin_dex_obj_t {int dummy; } ;
struct TYPE_5__ {TYPE_1__* o; } ;
struct TYPE_4__ {struct r_bin_dex_obj_t* bin_obj; } ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 char* dex_class_name_byid (struct r_bin_dex_obj_t*,int) ; 
 char* dex_field_name (struct r_bin_dex_obj_t*,int) ; 
 char* dex_get_proto (struct r_bin_dex_obj_t*,int) ; 
 char* dex_method_fullname (struct r_bin_dex_obj_t*,int) ; 
 int simplifiedDemangling ; 

__attribute__((used)) static char *getname(RBinFile *bf, int type, int idx, bool sd) {
	simplifiedDemangling = sd; // XXX kill globals
	struct r_bin_dex_obj_t *dex = bf->o->bin_obj;
	switch (type) {
	case 'm': // methods
		return dex_method_fullname (dex, idx);
	case 'c': // classes
		return dex_class_name_byid (dex, idx);
	case 'f': // fields
		return dex_field_name (dex, idx);
	case 'p': // proto
		return dex_get_proto (dex, idx);
	}
	return NULL;
}