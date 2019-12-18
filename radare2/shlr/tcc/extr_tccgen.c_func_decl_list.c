#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int t; } ;
struct TYPE_9__ {int v; TYPE_2__ type; struct TYPE_9__* next; } ;
typedef  TYPE_1__ Sym ;
typedef  TYPE_2__ CType ;
typedef  int /*<<< orphan*/  AttributeDef ;

/* Variables and functions */
 int SYM_FIELD ; 
 int /*<<< orphan*/  TCC_ERR (char*,int /*<<< orphan*/ ) ; 
 char TOK_ASM1 ; 
 char TOK_ASM2 ; 
 char TOK_ASM3 ; 
 char TOK_EOF ; 
 int /*<<< orphan*/  TYPE_DIRECT ; 
 int VT_STORAGE ; 
 int /*<<< orphan*/  convert_parameter_type (TYPE_2__*) ; 
 int /*<<< orphan*/  expect (char*) ; 
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_enum (TYPE_2__*) ; 
 scalar_t__ is_structured (TYPE_2__*) ; 
 int /*<<< orphan*/  next () ; 
 int /*<<< orphan*/  parse_btype (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char) ; 
 scalar_t__ tcc_nerr () ; 
 char tok ; 
 int /*<<< orphan*/  type_decl (TYPE_2__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void func_decl_list(Sym *func_sym) {
	AttributeDef ad;
	int v;
	Sym *s = NULL;
	CType btype, type;

	/* parse each declaration */
	while (tcc_nerr () == 0 && tok != '{' && tok != ';' && tok != ',' && tok != TOK_EOF &&
	       tok != TOK_ASM1 && tok != TOK_ASM2 && tok != TOK_ASM3) {
		if (!parse_btype (&btype, &ad)) {
			expect ("declaration list");
		}
		if ((is_enum(&btype) || is_structured(&btype)) && tok == ';') {
			/* we accept no variable after */
		} else {
			while (tcc_nerr () == 0) {
				int found;
				type = btype;
				type_decl (&type, &ad, &v, TYPE_DIRECT);
				/* find parameter in function parameter list */
				s = func_sym;
				found = 0;
				while ((s = s->next) != NULL) {
					if ((s->v & ~SYM_FIELD) == v) {
						found = 1;
						break;
					}
				}
				if (found == 0) {
					TCC_ERR ("declaration for parameter '%s' but no such parameter",
						get_tok_str (v, NULL));
				}
				/* check that no storage specifier except 'register' was given */
				if (type.t & VT_STORAGE) {
					TCC_ERR ("storage class specified for '%s'", get_tok_str (v, NULL));
				}
				convert_parameter_type (&type);
				/* we can add the type (NOTE: it could be local to the function) */
				if (s) {
					s->type = type;
				}
				/* accept other parameters */
				if (tok == ',') {
					next ();
				} else {
					break;
				}
			}
		}
		skip (';');
	}
}