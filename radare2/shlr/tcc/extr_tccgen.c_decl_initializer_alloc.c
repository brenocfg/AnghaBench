#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_21__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ TokenString ;
struct TYPE_36__ {TYPE_3__* sym; } ;
struct TYPE_35__ {int aligned; scalar_t__ packed; } ;
struct TYPE_34__ {int t; TYPE_3__* ref; } ;
struct TYPE_33__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_32__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_29__ {int t; TYPE_1__* ref; } ;
struct TYPE_31__ {scalar_t__ c; char* asm_label; TYPE_21__ type; struct TYPE_31__* next; } ;
struct TYPE_28__ {scalar_t__ c; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ ParseState ;
typedef  TYPE_5__ CValue ;
typedef  TYPE_6__ CType ;
typedef  TYPE_7__ AttributeDef ;

/* Variables and functions */
 int /*<<< orphan*/  TCC_ERR (char*,...) ; 
 char TOK_LSTR ; 
 char TOK_STR ; 
 int VT_ARRAY ; 
 int VT_CONST ; 
 int VT_EXTERN ; 
 int VT_LOCAL ; 
 int VT_SYM ; 
 int VT_VALMASK ; 
 int VT_WEAK ; 
 int /*<<< orphan*/  decl_initializer (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_compatible_types (TYPE_21__*,TYPE_6__*) ; 
 scalar_t__ is_struct (TYPE_6__*) ; 
 int loc ; 
 int /*<<< orphan*/  macro_ptr ; 
 int /*<<< orphan*/  next () ; 
 int pointed_size (TYPE_21__*) ; 
 int /*<<< orphan*/  save_parse_state (TYPE_4__*) ; 
 TYPE_3__* sym_find (int) ; 
 TYPE_3__* sym_push (int,TYPE_6__*,int,int) ; 
 scalar_t__ tcc_nerr () ; 
 char tok ; 
 int /*<<< orphan*/  tok_str_add (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tok_str_add_tok (TYPE_2__*) ; 
 int /*<<< orphan*/  tok_str_new (TYPE_2__*) ; 
 int type_size (TYPE_6__*,int*) ; 
 int /*<<< orphan*/  vset (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  vsetc (TYPE_6__*,int,TYPE_5__*) ; 
 TYPE_9__* vtop ; 
 int /*<<< orphan*/  weaken_symbol (TYPE_3__*) ; 

__attribute__((used)) static void decl_initializer_alloc(CType *type, AttributeDef *ad, int r, int has_init, int v, char *asm_label, int scope) {
	int size, align, addr;
	int level;
	ParseState saved_parse_state = {
		0
	};
	TokenString init_str;
	Sym *flexible_array;

	flexible_array = NULL;
	if (is_struct(type)) {
		Sym *field;
		field = type->ref;
		while (field && field->next)
			field = field->next;
		if (field && (field->type.t & VT_ARRAY) && (field->type.ref->c < 0)) {
			flexible_array = field;
		}
	}

	size = type_size (type, &align);
	/* If unknown size, we must evaluate it before
	   evaluating initializers because
	   initializers can generate global data too
	   (e.g. string pointers or ISOC99 compound
	   literals). It also simplifies local
	   initializers handling */
	tok_str_new (&init_str);
	if (size < 0 || (flexible_array && has_init)) {
		if (!has_init) {
			TCC_ERR ("unknown type size");
		}
		/* get all init string */
		if (has_init == 2) {
			/* only get strings */
			while (tok == TOK_STR || tok == TOK_LSTR) {
				tok_str_add_tok (&init_str);
				next ();
			}
		} else {
			level = 0;
			while (tcc_nerr() == 0 && (level > 0 || (tok != ',' && tok != ';'))) {
				if (tok < 0) {
					TCC_ERR ("unexpected end of file in initializer");
				}
				tok_str_add_tok (&init_str);
				if (tok == '{') {
					level++;
				} else if (tok == '}') {
					level--;
					if (level <= 0) {
						next ();
						break;
					}
				}
				next ();
			}
		}
		tok_str_add (&init_str, -1);
		tok_str_add (&init_str, 0);

		/* compute size */
		save_parse_state (&saved_parse_state);

		macro_ptr = init_str.str;
		next ();
		decl_initializer (type, 0, 1, 1);
		/* prepare second initializer parsing */
		macro_ptr = init_str.str;
		next ();

		/* if still unknown size, error */
		size = type_size (type, &align);
		if (size < 0) {
			TCC_ERR ("unknown type size");
		}
	}
	if (flexible_array) {
		size += flexible_array->type.ref->c * pointed_size (&flexible_array->type);
	}
	/* take into account specified alignment if bigger */
	if (ad->aligned) {
		if (ad->aligned > align) {
			align = ad->aligned;
		}
	} else if (ad->packed) {
		align = 1;
	}
	if ((r & VT_VALMASK) == VT_LOCAL) {
		loc = (loc - size) & - align;
		addr = loc;
		if (v) {
			/* local variable */
			sym_push (v, type, r, addr);
		} else {
			/* push local reference */
			vset (type, r, addr);
		}
	} else {
		Sym *sym;

		sym = NULL;
		if (v && scope == VT_CONST) {
			/* see if the symbol was already defined */
			sym = sym_find (v);
			if (sym) {
				if (!is_compatible_types (&sym->type, type)) {
					TCC_ERR ("incompatible types for redefinition of '%s'",
						get_tok_str (v, NULL));
				}
				if (sym->type.t & VT_EXTERN) {
					/* if the variable is extern, it was not allocated */
					sym->type.t &= ~VT_EXTERN;
					/* set array size if it was ommited in extern
					   declaration */
					if ((sym->type.t & VT_ARRAY) &&
					    sym->type.ref->c < 0 &&
					    type->ref->c >= 0) {
						sym->type.ref->c = type->ref->c;
					}
				} else {
					/* we accept several definitions of the same
					   global variable. this is tricky, because we
					   must play with the SHN_COMMON type of the symbol */
					/* XXX: should check if the variable was already
					   initialized. It is incorrect to initialized it
					   twice */
					/* no init data, we won't add more to the symbol */
					if (!has_init) {
						goto no_alloc;
					}
				}
			}
		}

		if (v) {
			if (scope != VT_CONST || !sym) {
				sym = sym_push (v, type, r | VT_SYM, 0);
				sym->asm_label = asm_label;
			}
		} else {
			CValue cval = { 0 };
			vsetc (type, VT_CONST | VT_SYM, &cval);
			vtop->sym = sym;
		}
		/* patch symbol weakness */
		if ((type->t & VT_WEAK) && sym) {
			weaken_symbol (sym);
		}
	}
no_alloc:
	;
}