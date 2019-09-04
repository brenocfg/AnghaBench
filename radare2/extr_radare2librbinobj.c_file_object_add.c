#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rbin; int /*<<< orphan*/  objs; } ;
typedef  int /*<<< orphan*/  RBinObject ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  r_bin_file_set_cur_binfile_obj (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 

__attribute__((used)) static bool file_object_add(RBinFile *binfile, RBinObject *o) {
	r_return_val_if_fail (binfile && o, false);
	r_list_append (binfile->objs, o);
	r_bin_file_set_cur_binfile_obj (binfile->rbin, binfile, o);
	return true;
}