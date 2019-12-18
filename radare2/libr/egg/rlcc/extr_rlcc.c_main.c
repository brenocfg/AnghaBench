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
struct TYPE_9__ {int /*<<< orphan*/ * error; TYPE_2__* output; } ;
typedef  TYPE_1__ mpc_result_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_err_t ;
struct TYPE_10__ {int children_num; int /*<<< orphan*/  contents; int /*<<< orphan*/  tag; struct TYPE_10__** children; } ;
typedef  TYPE_2__ mpc_ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPCA_LANG_DEFAULT ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mpc_ast_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_ast_print (TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_ast_print_to (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_cleanup (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_err_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_err_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_new (char*) ; 
 scalar_t__ mpc_parse_contents (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ mpc_parse_pipe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * mpca_lang (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processNode (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

int main(int argc, char **argv) {
	mpc_parser_t* Ident     = mpc_new("ident");
	mpc_parser_t* Number    = mpc_new("number");
	mpc_parser_t* Character = mpc_new("character");
	mpc_parser_t* String    = mpc_new("string");
	mpc_parser_t* Factor    = mpc_new("factor");
	mpc_parser_t* Term      = mpc_new("term");
	mpc_parser_t* Lexp      = mpc_new("lexp");
	mpc_parser_t* Stmt      = mpc_new("stmt");
	mpc_parser_t* Exp       = mpc_new("exp");
	mpc_parser_t* Vartype   = mpc_new("vartype");
	mpc_parser_t* Typeident = mpc_new("typeident");
	mpc_parser_t* Decls     = mpc_new("decls");
	mpc_parser_t* Args      = mpc_new("args");
	mpc_parser_t* Body      = mpc_new("body");
	mpc_parser_t* Comment   = mpc_new("comment");
	mpc_parser_t* Linecomment   = mpc_new("linecomment");
	mpc_parser_t* Asm = mpc_new("asm");
	mpc_parser_t* Procedure = mpc_new("procedure");
	mpc_parser_t* CProcedure = mpc_new("cprocedure");
	mpc_parser_t* Sigdef    = mpc_new("sigdef");
	mpc_parser_t* Sigbody   = mpc_new("sigbody");
	mpc_parser_t* Includes  = mpc_new("includes");
	mpc_parser_t* Smallc    = mpc_new("smallc");

	mpc_err_t* err = mpca_lang(MPCA_LANG_DEFAULT,
			" ident     : /[a-zA-Z_][a-zA-Z0-9_]*/ ;                           \n"
			" number    : /[0-9]+/ ;                                           \n"
			" character : /'.'/ ;                                              \n"
			" string    : /\"(\\\\.|[^\"])*\"/ ;                               \n"
			"                                                                  \n"
			" factor    : '(' <lexp> ')'                                       \n"
			"           | <number>                                             \n"
			"           | <character>                                          \n"
			"           | <string>                                             \n"
			"           | <ident> '(' <lexp>? (',' <lexp>)* ')'                \n"
			"           | <ident> ;                                            \n"
			"                                                                  \n"
			" term      : <factor> (('*' | '/' | '%') <factor>)* ;             \n"
			" lexp      : <term> (('+' | '-') <term>)* ;                       \n"
			"                                                                  \n"
			" stmt      : '{' <stmt>* '}'                                      \n"
			"           | \"while\" '(' <exp> ')' <stmt>                       \n"
			"           | \"if\"    '(' <exp> ')' <stmt>                       \n"
			"           | <ident> '=' <lexp> ';'                               \n"
			"           | \"print\" '(' <lexp>? ')' ';'                        \n"
			"           | \"return\" <lexp>? ';'                               \n"
			"           | <ident> '(' (<number>|<ident>|<string>)? (',' (<string>|<number>|<ident>))* ')' ';' ;        \n"
			"                                                                  \n"
			" exp       : <lexp> '>' <lexp>                                    \n"
			"           | <lexp> '<' <lexp>                                    \n"
			"           | <lexp> \">=\" <lexp>                                 \n"
			"           | <lexp> \"<=\" <lexp>                                 \n"
			"           | <lexp> \"!=\" <lexp>                                 \n"
			"           | <lexp> \"==\" <lexp> ;                               \n"
			"                                                                  \n"
			" vartype   : (\"int\" | \"char\") ;                               \n"
			" typeident : <vartype> <ident> ;                                  \n"
			" decls     : (<typeident> ';')* ;                                 \n"
			" args      : <typeident>? (',' <typeident>)* ;                    \n"
			" body      : '{' <decls> <stmt>* '}' ;                            \n"
			" comment   : /\\/\\*([^\\*])*\\*\\// ;                            \n"
			" linecomment : /\\/\\/([^\\n])*/ ;                                \n"
			" asm       : /\\:([^\\n])*/ ;                                \n"
			" procedure : <ident> '@' \"global\" '(' <number>? ')' <body> ; \n"
			" cprocedure : <vartype> <ident> '(' <args> ')' <body> ; \n"
			" sigdef    : <ident> '@' <ident> '(' <number> ')' ';' ; \n"
			" sigbody   : '@' <ident> '(' <number> ')' ';' ; \n"
			" includes  : (\"#include\" <string>)* ;                           \n"
			" smallc    : /^/ (<comment>|<asm>|<linecomment>|<sigdef>|<sigbody>|<procedure>|<cprocedure>)* <includes> <decls> /$/ ; \n",
		Ident, Number, Character, String, Factor, Term, Lexp, Stmt, Exp,
		Vartype, Typeident, Decls, Args, Body, Comment, Linecomment, Asm, Procedure, CProcedure,
		Sigdef, Sigbody, Includes, Smallc, NULL);

	if (err != NULL) {
		mpc_err_print (err);
		mpc_err_delete (err);
		exit(1);
	}

#if 1
	if (argc > 1) {

		mpc_result_t r;
		if (mpc_parse_contents(argv[1], Smallc, &r)) {
			mpc_ast_print_to(r.output, stderr);
			{
				int i;
				mpc_ast_t *root = r.output;
				for (i=0; i< root->children_num; i++) {
					mpc_ast_t *node = root->children[i];
					eprintf ("; TAG = %s    (%s)\n", node->tag, node->contents);
					processNode (node);
				}
			}
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

	} else {

		mpc_result_t r;
		if (mpc_parse_pipe("<stdin>", stdin, Smallc, &r)) {
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
	}
#endif

	mpc_cleanup(17, Ident, Number, Character, String, Factor, Term, Lexp, Stmt, Exp,
			Vartype, Typeident, Decls, Args, Body, Comment, Procedure, CProcedure,
			Sigdef, Includes, Smallc);

	return 0;

}