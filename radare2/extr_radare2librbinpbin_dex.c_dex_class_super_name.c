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
struct TYPE_11__ {int super_class; } ;
struct TYPE_8__ {int types_size; } ;
struct TYPE_10__ {TYPE_2__* types; TYPE_1__ header; } ;
struct TYPE_9__ {int descriptor_id; } ;
typedef  TYPE_3__ RBinDexObj ;
typedef  TYPE_4__ RBinDexClass ;

/* Variables and functions */
 char const* getstr (TYPE_3__*,int) ; 

__attribute__((used)) static const char *dex_class_super_name(RBinDexObj *bin, RBinDexClass *c) {
	int cid, tid;
	if (!bin || !c || !bin->types) {
		return NULL;
	}
	cid = c->super_class;
	if (cid < 0 || cid >= bin->header.types_size) {
		return NULL;
	}
	tid = bin->types[cid].descriptor_id;
	return getstr (bin, tid);
}