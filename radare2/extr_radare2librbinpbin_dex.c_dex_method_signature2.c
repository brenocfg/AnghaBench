#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  size_t ut32 ;
typedef  size_t ut16 ;
struct TYPE_10__ {int method_size; size_t prototypes_size; size_t types_size; } ;
struct TYPE_12__ {size_t size; TYPE_4__* types; TYPE_3__ header; int /*<<< orphan*/  b; TYPE_2__* protos; TYPE_1__* methods; } ;
struct TYPE_11__ {int /*<<< orphan*/  descriptor_id; } ;
struct TYPE_9__ {size_t parameters_off; } ;
struct TYPE_8__ {size_t proto_id; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_5__ RBinDexObj ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 char* getstr (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 
 size_t read16 (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t read32 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static RList *dex_method_signature2(RBinDexObj *bin, int method_idx) {
	ut32 proto_id, params_off, list_size;
	ut16 type_idx;
	int i;

	RList *params = r_list_newf (free);
	if (!params) {
		return NULL;
	}
	if (method_idx < 0 || method_idx >= bin->header.method_size) {
		goto out_error;
	}
	proto_id = bin->methods[method_idx].proto_id;
	if (proto_id >= bin->header.prototypes_size) {
		goto out_error;
	}
	params_off = bin->protos[proto_id].parameters_off;
	if (params_off  >= bin->size) {
		goto out_error;
	}
	if (!params_off) {
		return params;
	}
	list_size = read32 (bin->b, params_off);
	for (i = 0; i < list_size; i++) {
		ut64 of = params_off + 4 + (i * 2);
		if (of >= bin->size || of < params_off) {
			break;
		}
		type_idx = read16 (bin->b, of);
		if (type_idx >= bin->header.types_size || type_idx > bin->size) {
			break;
		}
		char *buff = getstr (bin, bin->types[type_idx].descriptor_id);
		if (!buff) {
			break;
		}
		r_list_append (params, buff);
	}
	return params;
out_error:
	r_list_free (params);
	return NULL;
}