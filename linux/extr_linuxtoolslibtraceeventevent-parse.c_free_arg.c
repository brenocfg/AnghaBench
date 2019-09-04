#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {struct print_arg* args; } ;
struct TYPE_14__ {struct print_arg* right; struct print_arg* left; struct print_arg* op; } ;
struct TYPE_13__ {struct print_arg* index; } ;
struct TYPE_24__ {struct print_arg* bitmask; } ;
struct TYPE_23__ {struct print_arg* string; } ;
struct TYPE_22__ {struct print_arg* item; struct print_arg* type; } ;
struct TYPE_21__ {struct print_arg* el_size; struct print_arg* count; struct print_arg* field; } ;
struct TYPE_20__ {struct print_arg* size; struct print_arg* field; } ;
struct TYPE_19__ {int /*<<< orphan*/  symbols; struct print_arg* field; } ;
struct TYPE_18__ {int /*<<< orphan*/  flags; struct print_arg* delim; struct print_arg* field; } ;
struct TYPE_17__ {struct print_arg* name; } ;
struct TYPE_16__ {struct print_arg* atom; } ;
struct print_arg {int type; struct print_arg* next; TYPE_12__ func; TYPE_11__ op; TYPE_10__ dynarray; TYPE_9__ bitmask; TYPE_8__ string; TYPE_7__ typecast; TYPE_6__ int_array; TYPE_5__ hex; TYPE_4__ symbol; TYPE_3__ flags; TYPE_2__ field; TYPE_1__ atom; } ;

/* Variables and functions */
#define  PRINT_ATOM 143 
#define  PRINT_BITMASK 142 
#define  PRINT_BSTRING 141 
#define  PRINT_DYNAMIC_ARRAY 140 
#define  PRINT_DYNAMIC_ARRAY_LEN 139 
#define  PRINT_FIELD 138 
#define  PRINT_FLAGS 137 
#define  PRINT_FUNC 136 
#define  PRINT_HEX 135 
#define  PRINT_HEX_STR 134 
#define  PRINT_INT_ARRAY 133 
#define  PRINT_NULL 132 
#define  PRINT_OP 131 
#define  PRINT_STRING 130 
#define  PRINT_SYMBOL 129 
#define  PRINT_TYPE 128 
 int /*<<< orphan*/  free (struct print_arg*) ; 
 int /*<<< orphan*/  free_flag_sym (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_arg(struct print_arg *arg)
{
	struct print_arg *farg;

	if (!arg)
		return;

	switch (arg->type) {
	case PRINT_ATOM:
		free(arg->atom.atom);
		break;
	case PRINT_FIELD:
		free(arg->field.name);
		break;
	case PRINT_FLAGS:
		free_arg(arg->flags.field);
		free(arg->flags.delim);
		free_flag_sym(arg->flags.flags);
		break;
	case PRINT_SYMBOL:
		free_arg(arg->symbol.field);
		free_flag_sym(arg->symbol.symbols);
		break;
	case PRINT_HEX:
	case PRINT_HEX_STR:
		free_arg(arg->hex.field);
		free_arg(arg->hex.size);
		break;
	case PRINT_INT_ARRAY:
		free_arg(arg->int_array.field);
		free_arg(arg->int_array.count);
		free_arg(arg->int_array.el_size);
		break;
	case PRINT_TYPE:
		free(arg->typecast.type);
		free_arg(arg->typecast.item);
		break;
	case PRINT_STRING:
	case PRINT_BSTRING:
		free(arg->string.string);
		break;
	case PRINT_BITMASK:
		free(arg->bitmask.bitmask);
		break;
	case PRINT_DYNAMIC_ARRAY:
	case PRINT_DYNAMIC_ARRAY_LEN:
		free(arg->dynarray.index);
		break;
	case PRINT_OP:
		free(arg->op.op);
		free_arg(arg->op.left);
		free_arg(arg->op.right);
		break;
	case PRINT_FUNC:
		while (arg->func.args) {
			farg = arg->func.args;
			arg->func.args = farg->next;
			free_arg(farg);
		}
		break;

	case PRINT_NULL:
	default:
		break;
	}

	free(arg);
}