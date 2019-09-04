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
struct TYPE_5__ {TYPE_1__* o; } ;
struct TYPE_4__ {int /*<<< orphan*/  bin_obj; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int RBinAddr ; 
 int /*<<< orphan*/  R_FREE (int) ; 
 int /*<<< orphan*/  R_NEW0 (int) ; 
 int addr ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  r_bin_omf_get_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList *entries(RBinFile *bf) {
	RList *ret;
	RBinAddr *addr;

	if (!(ret = r_list_newf (free))) {
		return NULL;
	}
	if (!(addr = R_NEW0 (RBinAddr))) {
		r_list_free (ret);
		return NULL;
	}
	if (!r_bin_omf_get_entry (bf->o->bin_obj, addr)) {
		R_FREE (addr);
	} else {
		r_list_append (ret, addr);
	}
	return ret;
}