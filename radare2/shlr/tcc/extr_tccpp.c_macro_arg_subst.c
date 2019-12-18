#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int len; char* str; } ;
typedef  TYPE_2__ TokenString ;
struct TYPE_26__ {int size; scalar_t__ data; } ;
struct TYPE_25__ {TYPE_5__* cstr; } ;
struct TYPE_22__ {scalar_t__ t; } ;
struct TYPE_24__ {int* d; TYPE_1__ type; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ CValue ;
typedef  TYPE_5__ CString ;

/* Variables and functions */
 int /*<<< orphan*/  TOK_GET (int*,int const**,TYPE_4__*) ; 
 int TOK_IDENT ; 
 int TOK_STR ; 
 int const TOK_TWOSHARPS ; 
 int /*<<< orphan*/  check_space (int,int*) ; 
 int /*<<< orphan*/  cstr_cat (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstr_ccat (TYPE_5__*,char) ; 
 int /*<<< orphan*/  cstr_free (TYPE_5__*) ; 
 int /*<<< orphan*/  cstr_new (TYPE_5__*) ; 
 int /*<<< orphan*/  get_tok_str (int,TYPE_4__*) ; 
 scalar_t__ gnu_ext ; 
 int /*<<< orphan*/  macro_subst (TYPE_2__*,TYPE_3__**,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_3__* sym_find2 (TYPE_3__*,int) ; 
 scalar_t__ tcc_nerr () ; 
 int /*<<< orphan*/  tok_str_add (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tok_str_add2 (TYPE_2__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  tok_str_new (TYPE_2__*) ; 

__attribute__((used)) static int *macro_arg_subst(Sym **nested_list, const int *macro_str, Sym *args)
{
	int last_tok, t, spc;
	const int *st;
	Sym *s;
	CValue cval;
	TokenString str;
	CString cstr;

	tok_str_new (&str);
	last_tok = 0;
	while (tcc_nerr () == 0) {
		TOK_GET (&t, &macro_str, &cval);
		if (!t) {
			break;
		}
		if (t == '#') {
			/* stringize */
			TOK_GET (&t, &macro_str, &cval);
			if (!t) {
				break;
			}
			s = sym_find2 (args, t);
			if (s) {
				cstr_new (&cstr);
				st = s->d;
				spc = 0;
				while (*st) {
					TOK_GET (&t, &st, &cval);
					if (!check_space (t, &spc)) {
						cstr_cat (&cstr, get_tok_str (t, &cval));
					}
				}
				cstr.size -= spc;
				cstr_ccat (&cstr, '\0');
#ifdef PP_DEBUG
				printf ("stringize: %s\n", (char *) cstr.data);
#endif
				/* add string */
				cval.cstr = &cstr;
				tok_str_add2 (&str, TOK_STR, &cval);
				cstr_free (&cstr);
			} else {
				tok_str_add2 (&str, t, &cval);
			}
		} else if (t >= TOK_IDENT) {
			s = sym_find2 (args, t);
			if (s) {
				st = s->d;
				/* if '##' is present before or after, no arg substitution */
				if (*macro_str == TOK_TWOSHARPS || last_tok == TOK_TWOSHARPS) {
					/* special case for var arg macros : ## eats the
					   ',' if empty VA_ARGS variable. */
					/* XXX: test of the ',' is not 100%
					   reliable. should fix it to avoid security
					   problems */
					if (gnu_ext && s->type.t &&
					    last_tok == TOK_TWOSHARPS &&
					    str.len >= 2 && str.str[str.len - 2] == ',') {
						if (*st == 0) {
							/* suppress ',' '##' */
							str.len -= 2;
						} else {
							/* suppress '##' and add variable */
							str.len--;
							goto add_var;
						}
					} else {
						int t1;
add_var:
						for (;;) {
							TOK_GET (&t1, &st, &cval);
							if (!t1) {
								break;
							}
							tok_str_add2 (&str, t1, &cval);
						}
					}
				} else {
					/* NOTE: the stream cannot be read when macro
					   substituing an argument */
					macro_subst (&str, nested_list, st, NULL);
				}
			} else {
				tok_str_add (&str, t);
			}
		} else {
			tok_str_add2 (&str, t, &cval);
		}
		last_tok = t;
	}
	tok_str_add (&str, 0);
	return str.str;
}