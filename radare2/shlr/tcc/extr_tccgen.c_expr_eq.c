#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char TOK_A_DIV ; 
 char TOK_A_MOD ; 
 char TOK_A_OR ; 
 char TOK_A_SAR ; 
 char TOK_A_SHL ; 
 char TOK_A_XOR ; 
 int /*<<< orphan*/  expr_cond () ; 
 int /*<<< orphan*/  next () ; 
 int /*<<< orphan*/  test_lvalue () ; 
 char tok ; 
 int /*<<< orphan*/  vdup () ; 

__attribute__((used)) static void expr_eq(void) {
	int t;

	expr_cond ();
	if (tok == '=' ||
	    (tok >= TOK_A_MOD && tok <= TOK_A_DIV) ||
	    tok == TOK_A_XOR || tok == TOK_A_OR ||
	    tok == TOK_A_SHL || tok == TOK_A_SAR) {
		test_lvalue ();
		t = tok;
		next ();
		if (t == '=') {
			expr_eq ();
		} else {
			vdup ();
			expr_eq ();
		}
	}
}