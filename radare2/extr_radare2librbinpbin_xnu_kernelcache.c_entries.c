#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_10__ {scalar_t__ entry; } ;
struct TYPE_9__ {TYPE_2__* o; } ;
struct TYPE_8__ {scalar_t__ bin_obj; } ;
struct TYPE_7__ {scalar_t__ pa2va_exec; TYPE_5__* mach0; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RKernelCacheObj ;
typedef  TYPE_2__ RBinObject ;
typedef  TYPE_3__ RBinFile ;
typedef  int /*<<< orphan*/  RBinAddr ;

/* Variables and functions */
 int /*<<< orphan*/  R_K_CONSTRUCTOR_TO_ENTRY ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * newEntry (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_constructors (TYPE_1__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList *entries(RBinFile *bf) {
	RList *ret;
	RBinObject *obj = bf ? bf->o : NULL;

	if (!obj || !obj->bin_obj || !(ret = r_list_newf (free))) {
		return NULL;
	}

	RKernelCacheObj *kobj = (RKernelCacheObj*) obj->bin_obj;
	ut64 entry_vaddr = kobj->mach0->entry;
	if (kobj->pa2va_exec <= entry_vaddr) {
		ut64 entry_paddr = entry_vaddr - kobj->pa2va_exec;
		RBinAddr *ba = newEntry (entry_paddr, entry_vaddr, 0);
		if (ba) {
			r_list_append (ret, ba);
		}
	}

	process_constructors (kobj, kobj->mach0, ret, 0, true, R_K_CONSTRUCTOR_TO_ENTRY, NULL);

	return ret;
}