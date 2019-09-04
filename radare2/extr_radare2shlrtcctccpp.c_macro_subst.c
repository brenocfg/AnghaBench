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
struct macro_level {int* p; struct macro_level* prev; } ;
typedef  int /*<<< orphan*/  TokenString ;
typedef  int /*<<< orphan*/  Sym ;
typedef  int /*<<< orphan*/  CValue ;

/* Variables and functions */
 int PARSE_FLAG_SPACES ; 
 int /*<<< orphan*/  TOK_GET (int*,int const**,int /*<<< orphan*/ *) ; 
 int TOK_NOSUBST ; 
 int /*<<< orphan*/  check_space (int,int*) ; 
 int /*<<< orphan*/ * define_find (int) ; 
 int* macro_ptr ; 
 int macro_subst_tok (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct macro_level**) ; 
 int* macro_twosharps (int const*) ; 
 int parse_flags ; 
 scalar_t__ sym_find2 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tcc_nerr () ; 
 int tok ; 
 int /*<<< orphan*/  tok_str_add (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  tok_str_add2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok_str_free (int*) ; 

__attribute__((used)) static void macro_subst(TokenString *tok_str, Sym **nested_list,
			const int *macro_str, struct macro_level **can_read_stream)
{
	Sym *s;
	int *macro_str1;
	const int *ptr;
	int t, ret, spc;
	CValue cval;
	struct macro_level ml;
	int force_blank;

	/* first scan for '##' operator handling */
	ptr = macro_str;
	macro_str1 = macro_twosharps (ptr);

	if (macro_str1) {
		ptr = macro_str1;
	}
	spc = 0;
	force_blank = 0;

	while (tcc_nerr () == 0) {
		/* NOTE: ptr == NULL can only happen if tokens are read from
		   file stream due to a macro function call */
		if (ptr == NULL) {
			break;
		}
		TOK_GET (&t, &ptr, &cval);
		if (t == 0) {
			break;
		}
		if (t == TOK_NOSUBST) {
			/* following token has already been subst'd. just copy it on */
			tok_str_add2 (tok_str, TOK_NOSUBST, NULL);
			TOK_GET (&t, &ptr, &cval);
			goto no_subst;
		}
		s = define_find (t);
		if (s != NULL) {
			/* if nested substitution, do nothing */
			if (sym_find2 (*nested_list, t)) {
				/* and mark it as TOK_NOSUBST, so it doesn't get subst'd again */
				tok_str_add2 (tok_str, TOK_NOSUBST, NULL);
				goto no_subst;
			}
			ml.p = macro_ptr;
			if (can_read_stream) {
				ml.prev = *can_read_stream, *can_read_stream = &ml;
			}
			macro_ptr = (int *) ptr;
			tok = t;
			ret = macro_subst_tok (tok_str, nested_list, s, can_read_stream);
			ptr = (int *) macro_ptr;
			macro_ptr = ml.p;
			if (can_read_stream && *can_read_stream == &ml) {
				*can_read_stream = ml.prev;
			}
			if (ret != 0) {
				goto no_subst;
			}
			if (parse_flags & PARSE_FLAG_SPACES) {
				force_blank = 1;
			}
		} else {
no_subst:
			if (force_blank) {
				tok_str_add (tok_str, ' ');
				spc = 1;
				force_blank = 0;
			}
			if (!check_space (t, &spc)) {
				tok_str_add2 (tok_str, t, &cval);
			}
		}
	}
	if (macro_str1) {
		tok_str_free (macro_str1);
	}
}