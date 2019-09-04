#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ TokenString ;
struct TYPE_7__ {int i; } ;

/* Variables and functions */
 int TOK_CINT ; 
 int TOK_DEFINED ; 
 int TOK_EOF ; 
 int TOK_IDENT ; 
 int TOK_LINEFEED ; 
 scalar_t__ define_find (int) ; 
 int expr_const () ; 
 int /*<<< orphan*/ * macro_ptr ; 
 int /*<<< orphan*/  next () ; 
 int /*<<< orphan*/  next_nomacro () ; 
 int tok ; 
 int /*<<< orphan*/  tok_str_add (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tok_str_add_tok (TYPE_1__*) ; 
 int /*<<< orphan*/  tok_str_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok_str_new (TYPE_1__*) ; 
 TYPE_2__ tokc ; 

__attribute__((used)) static int expr_preprocess(void)
{
	int c, t;
	TokenString str;

	tok_str_new (&str);
	while (tok != TOK_LINEFEED && tok != TOK_EOF) {
		next ();/* do macro subst */
		if (tok == TOK_DEFINED) {
			next_nomacro ();
			t = tok;
			if (t == '(') {
				next_nomacro ();
			}
			c = define_find (tok) != 0;
			if (t == '(') {
				next_nomacro ();
			}
			tok = TOK_CINT;
			tokc.i = c;
		} else if (tok >= TOK_IDENT) {
			/* if undefined macro */
			tok = TOK_CINT;
			tokc.i = 0;
		}
		tok_str_add_tok (&str);
	}
	tok_str_add (&str, -1);	/* simulate end of file */
	tok_str_add (&str, 0);
	/* now evaluate C constant expression */
	macro_ptr = str.str;
	next ();
	c = expr_const ();
	macro_ptr = NULL;
	tok_str_free (str.str);
	return c != 0;
}