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
struct TYPE_5__ {int t; TYPE_1__* ref; } ;
struct TYPE_4__ {int asm_label; int /*<<< orphan*/  r; int /*<<< orphan*/  v; } ;
typedef  TYPE_2__ CType ;

/* Variables and functions */
 int VT_BTYPE ; 
#define  VT_ENUM 135 
#define  VT_INT16 134 
#define  VT_INT32 133 
#define  VT_INT64 132 
#define  VT_INT8 131 
#define  VT_PTR 130 
#define  VT_STRUCT 129 
#define  VT_UNION 128 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 char* get_tok_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dump_type(CType *type, int depth) {
	if (depth <= 0) {
		return;
	}
	eprintf ("------------------------\n");
	int bt = type->t & VT_BTYPE;
	eprintf ("BTYPE = %d ", bt);
	switch (bt) {
	case VT_UNION: eprintf ("[UNION]\n");
		break;
	case VT_STRUCT: eprintf ("[STRUCT]\n");
		break;
	case VT_PTR: eprintf ("[PTR]\n");
		break;
	case VT_ENUM: eprintf ("[ENUM]\n");
		break;
	case VT_INT64: eprintf ("[INT64_T]\n");
		break;
	case VT_INT32: eprintf ("[INT32_T]\n");
		break;
	case VT_INT16: eprintf ("[INT16_T]\n");
		break;
	case VT_INT8: eprintf ("[INT8_T]\n");
		break;
	default:
		eprintf ("\n");
		break;
	}
	if (type->ref) {
		eprintf ("v = %d\n", type->ref->v);
		char *varstr = NULL;
		varstr = get_tok_str (type->ref->v, NULL);
		if (varstr) {
			eprintf ("var = %s\n", varstr);
		}
		if (type->ref->asm_label) {
			eprintf ("asm_label = %s\n", type->ref->asm_label);
		}
		eprintf ("r = %d\n", type->ref->r);
		eprintf ("associated type:\n");
		// dump_type(&(type->ref->type), --depth);
	}
}