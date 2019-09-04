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
struct TYPE_7__ {TYPE_1__* o; } ;
struct TYPE_6__ {int /*<<< orphan*/ * imports_list; } ;
struct TYPE_5__ {scalar_t__ bin_obj; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RBinNXOObj ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */

__attribute__((used)) static RList *imports(RBinFile *bf) {
	RBinNXOObj *bin;
	if (!bf || !bf->o || !bf->o->bin_obj) {
		return NULL;
	}
	bin = (RBinNXOObj*) bf->o->bin_obj;
	return bin->imports_list;
}