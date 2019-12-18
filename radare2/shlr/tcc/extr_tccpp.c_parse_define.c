#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  str; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ TokenString ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ Sym ;

/* Variables and functions */
 int MACRO_FUNC ; 
 int MACRO_OBJ ; 
 int SYM_FIELD ; 
 int TOK_DOTS ; 
 char TOK_EOF ; 
 int TOK_IDENT ; 
 char TOK_LINEFEED ; 
 char TOK_TWOSHARPS ; 
 int TOK___VA_ARGS__ ; 
 scalar_t__ check_space (char,int*) ; 
 int /*<<< orphan*/  define_push (int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  define_stack ; 
 char* get_tok_str (int,int /*<<< orphan*/ *) ; 
 scalar_t__ gnu_ext ; 
 int /*<<< orphan*/  next_nomacro () ; 
 int /*<<< orphan*/  next_nomacro_spc () ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 TYPE_2__* sym_push2 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcc_error (char*,...) ; 
 char tok ; 
 int /*<<< orphan*/  tok_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok_str_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok_str_add2 (TYPE_1__*,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok_str_new (TYPE_1__*) ; 
 int /*<<< orphan*/  tokc ; 

void parse_define(void)
{
	Sym *s, *first, **ps;
	int v, t, varg, is_vaargs, spc;
	TokenString str;

	v = tok;
	if (v < TOK_IDENT) {
		tcc_error ("invalid macro name '%s'", get_tok_str (tok, &tokc));
	}
	/* XXX: should check if same macro (ANSI) */
	first = NULL;
	t = MACRO_OBJ;
	/* '(' must be just after macro definition for MACRO_FUNC */
	next_nomacro_spc ();
	if (tok == '(') {
		next_nomacro ();
		ps = &first;
		while (tok != ')') {
			varg = tok;
			next_nomacro ();
			is_vaargs = 0;
			if (varg == TOK_DOTS) {
				varg = TOK___VA_ARGS__;
				is_vaargs = 1;
			} else if (tok == TOK_DOTS && gnu_ext) {
				is_vaargs = 1;
				next_nomacro ();
			}
			if (varg < TOK_IDENT) {
				tcc_error ("badly punctuated parameter list");
			}
			s = sym_push2 (&define_stack, varg | SYM_FIELD, is_vaargs, 0);
			if (!s) {
				return;
			}
			*ps = s;
			ps = &s->next;
			if (tok != ',') {
				break;
			}
			next_nomacro ();
		}
		if (tok == ')') {
			next_nomacro_spc ();
		}
		t = MACRO_FUNC;
	}
	tok_str_new (&str);
	spc = 2;
	/* EOF testing necessary for '-D' handling */
	while (tok != TOK_LINEFEED && tok != TOK_EOF) {
		/* remove spaces around ## and after '#' */
		if (TOK_TWOSHARPS == tok) {
			if (1 == spc) {
				--str.len;
			}
			spc = 2;
		} else if ('#' == tok) {
			spc = 2;
		} else if (check_space (tok, &spc)) {
			goto skip;
		}
		tok_str_add2 (&str, tok, &tokc);
skip:
		next_nomacro_spc ();
	}
	if (spc == 1) {
		--str.len;	/* remove trailing space */
	}
	tok_str_add (&str, 0);
#ifdef PP_DEBUG
	printf ("define %s %d: ", get_tok_str (v, NULL), t);
	tok_print (str.str);
#endif
	define_push (v, t, str.str, first);
}