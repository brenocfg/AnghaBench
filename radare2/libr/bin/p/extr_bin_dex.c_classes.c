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
struct TYPE_8__ {int /*<<< orphan*/ * classes_list; } ;
struct TYPE_7__ {TYPE_1__* o; } ;
struct TYPE_6__ {scalar_t__ bin_obj; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RBinFile ;
typedef  TYPE_3__ RBinDexObj ;

/* Variables and functions */
 int /*<<< orphan*/  dex_loadcode (TYPE_2__*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RList *classes(RBinFile *bf) {
	r_return_val_if_fail (bf && bf->o && bf->o->bin_obj, NULL);
	RBinDexObj *bin = (RBinDexObj*) bf->o->bin_obj;
	if (!bin->classes_list) {
		dex_loadcode (bf);
	}
	return bin->classes_list;
}