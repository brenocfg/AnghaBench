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
 int /*<<< orphan*/  free (char*) ; 
 char* getstr (TYPE_4__*,int) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 char* r_str_newf (char*,...) ; 
 scalar_t__ simplifiedDemangling ; 
 char* simplify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static char *dex_field_name(RBinDexObj *bin, int fid) {
	int cid, tid, type_id;
	r_return_val_if_fail (bin && bin->fields, NULL);

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
	const char *a = getstr (bin, bin->types[cid].descriptor_id);
	const char *b = getstr (bin, tid);
	const char *c = getstr (bin, bin->types[type_id].descriptor_id);
	if (simplifiedDemangling) {
		if (a && b && c) {
			char *_a = simplify(strdup (a));
			char *_b = simplify(strdup (b));
			char *_c = simplify(strdup (c));
			char *str =  r_str_newf ("(%s) %s.%s", _c, _a, _b);
			free (_a);
			free (_b);
			free (_c);
			return str;
		}
		return r_str_newf ("(%d) %d.%d",
				bin->types[type_id].descriptor_id,
				tid,
				bin->types[cid].descriptor_id
			     );
	}
	return (a && b && c)
		? r_str_newf ("%s->%s %s", a, b, c)
		: r_str_newf ("%d->%d %d", bin->types[cid].descriptor_id, tid, bin->types[type_id].descriptor_id);
}