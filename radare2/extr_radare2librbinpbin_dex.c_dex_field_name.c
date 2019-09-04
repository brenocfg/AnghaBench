#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fields_size; int types_size; } ;
struct TYPE_10__ {TYPE_3__* types; TYPE_2__* fields; TYPE_1__ header; } ;
struct TYPE_9__ {int descriptor_id; } ;
struct TYPE_8__ {int class_id; int type_id; int name_id; } ;
typedef  TYPE_4__ RBinDexObj ;

/* Variables and functions */
 int /*<<< orphan*/  getstr (TYPE_4__*,int) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *dex_field_name(RBinDexObj *bin, int fid) {
	int cid, tid, type_id;
	if (!bin || !bin->fields) {
		return NULL;
	}
	if (fid < 0 || fid >= bin->header.fields_size) {
		return NULL;
	}
	cid = bin->fields[fid].class_id;
	if (cid < 0 || cid >= bin->header.types_size) {
		return NULL;
	}
	type_id = bin->fields[fid].type_id;
	if (type_id < 0 || type_id >= bin->header.types_size) {
		return NULL;
	}
	tid = bin->fields[fid].name_id;
	return r_str_newf ("%s->%s %s", getstr (bin, bin->types[cid].descriptor_id),
		getstr (bin, tid), getstr (bin, bin->types[type_id].descriptor_id));
}