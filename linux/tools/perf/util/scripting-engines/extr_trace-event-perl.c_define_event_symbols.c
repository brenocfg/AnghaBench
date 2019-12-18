#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {struct tep_print_arg* right; struct tep_print_arg* left; int /*<<< orphan*/  op; } ;
struct TYPE_15__ {struct tep_print_arg* item; } ;
struct TYPE_14__ {struct tep_print_arg* el_size; struct tep_print_arg* count; struct tep_print_arg* field; } ;
struct TYPE_13__ {struct tep_print_arg* size; struct tep_print_arg* field; } ;
struct TYPE_12__ {int /*<<< orphan*/  symbols; struct tep_print_arg* field; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  delim; struct tep_print_arg* field; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  atom; } ;
struct tep_print_arg {int type; struct tep_print_arg* next; TYPE_8__ op; TYPE_7__ typecast; TYPE_6__ int_array; TYPE_5__ hex; TYPE_4__ symbol; TYPE_3__ flags; TYPE_2__ field; TYPE_1__ atom; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
#define  TEP_PRINT_ATOM 143 
#define  TEP_PRINT_BITMASK 142 
#define  TEP_PRINT_BSTRING 141 
#define  TEP_PRINT_DYNAMIC_ARRAY 140 
#define  TEP_PRINT_DYNAMIC_ARRAY_LEN 139 
#define  TEP_PRINT_FIELD 138 
#define  TEP_PRINT_FLAGS 137 
#define  TEP_PRINT_FUNC 136 
#define  TEP_PRINT_HEX 135 
#define  TEP_PRINT_HEX_STR 134 
#define  TEP_PRINT_INT_ARRAY 133 
#define  TEP_PRINT_NULL 132 
#define  TEP_PRINT_OP 131 
#define  TEP_PRINT_STRING 130 
#define  TEP_PRINT_SYMBOL 129 
#define  TEP_PRINT_TYPE 128 
 int /*<<< orphan*/  cur_field_name ; 
 int /*<<< orphan*/  define_flag_field (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_flag_value (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_flag_values (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_symbolic_field (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_symbolic_values (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int zero_flag_atom ; 

__attribute__((used)) static void define_event_symbols(struct tep_event *event,
				 const char *ev_name,
				 struct tep_print_arg *args)
{
	if (args == NULL)
		return;

	switch (args->type) {
	case TEP_PRINT_NULL:
		break;
	case TEP_PRINT_ATOM:
		define_flag_value(ev_name, cur_field_name, "0",
				  args->atom.atom);
		zero_flag_atom = 0;
		break;
	case TEP_PRINT_FIELD:
		free(cur_field_name);
		cur_field_name = strdup(args->field.name);
		break;
	case TEP_PRINT_FLAGS:
		define_event_symbols(event, ev_name, args->flags.field);
		define_flag_field(ev_name, cur_field_name, args->flags.delim);
		define_flag_values(args->flags.flags, ev_name, cur_field_name);
		break;
	case TEP_PRINT_SYMBOL:
		define_event_symbols(event, ev_name, args->symbol.field);
		define_symbolic_field(ev_name, cur_field_name);
		define_symbolic_values(args->symbol.symbols, ev_name,
				       cur_field_name);
		break;
	case TEP_PRINT_HEX:
	case TEP_PRINT_HEX_STR:
		define_event_symbols(event, ev_name, args->hex.field);
		define_event_symbols(event, ev_name, args->hex.size);
		break;
	case TEP_PRINT_INT_ARRAY:
		define_event_symbols(event, ev_name, args->int_array.field);
		define_event_symbols(event, ev_name, args->int_array.count);
		define_event_symbols(event, ev_name, args->int_array.el_size);
		break;
	case TEP_PRINT_BSTRING:
	case TEP_PRINT_DYNAMIC_ARRAY:
	case TEP_PRINT_DYNAMIC_ARRAY_LEN:
	case TEP_PRINT_STRING:
	case TEP_PRINT_BITMASK:
		break;
	case TEP_PRINT_TYPE:
		define_event_symbols(event, ev_name, args->typecast.item);
		break;
	case TEP_PRINT_OP:
		if (strcmp(args->op.op, ":") == 0)
			zero_flag_atom = 1;
		define_event_symbols(event, ev_name, args->op.left);
		define_event_symbols(event, ev_name, args->op.right);
		break;
	case TEP_PRINT_FUNC:
	default:
		pr_err("Unsupported print arg type\n");
		/* we should warn... */
		return;
	}

	if (args->next)
		define_event_symbols(event, ev_name, args->next);
}