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
struct TYPE_6__ {int types_size; } ;
struct TYPE_8__ {TYPE_2__* types; TYPE_1__ header; } ;
struct TYPE_7__ {int /*<<< orphan*/  descriptor_id; } ;
typedef  TYPE_3__ RBinDexObj ;

/* Variables and functions */
 char* getstr (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *dex_type_descriptor(RBinDexObj *bin, int type_idx) {
	if (type_idx < 0 || type_idx >= bin->header.types_size) {
		return NULL;
	}
	return getstr (bin, bin->types[type_idx].descriptor_id);
}