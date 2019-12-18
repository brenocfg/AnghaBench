#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int len; int* str; } ;
typedef  TYPE_1__ TokenString ;
struct TYPE_13__ {scalar_t__* buf_ptr; int /*<<< orphan*/  buffer; } ;
struct TYPE_12__ {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  CValue ;
typedef  TYPE_2__ CString ;

/* Variables and functions */
 int /*<<< orphan*/  TOK_GET (int*,int const**,int /*<<< orphan*/ *) ; 
 int TOK_NOSUBST ; 
 int TOK_TWOSHARPS ; 
 int /*<<< orphan*/  cstr_cat (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstr_ccat (TYPE_2__*,char) ; 
 int /*<<< orphan*/  cstr_free (TYPE_2__*) ; 
 int /*<<< orphan*/  cstr_new (TYPE_2__*) ; 
 TYPE_6__* file ; 
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  next_nomacro1 () ; 
 int /*<<< orphan*/  tcc_close () ; 
 scalar_t__ tcc_nerr () ; 
 int /*<<< orphan*/  tcc_open_bf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tcc_state ; 
 int /*<<< orphan*/  tcc_warning (char*,int,char*,char*) ; 
 int tok ; 
 int /*<<< orphan*/  tok_str_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok_str_add2 (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok_str_new (TYPE_1__*) ; 
 int /*<<< orphan*/  tokc ; 

__attribute__((used)) static inline int *macro_twosharps(const int *macro_str)
{
	const int *ptr;
	int t;
	TokenString macro_str1;
	CString cstr;
	int n, start_of_nosubsts;

	/* we search the first '##' */
	for (ptr = macro_str;;) {
		CValue cval;
		TOK_GET (&t, &ptr, &cval);
		if (t == TOK_TWOSHARPS) {
			break;
		}
		/* nothing more to do if end of string */
		if (t == 0) {
			return NULL;
		}
	}

	/* we saw '##', so we need more processing to handle it */
	start_of_nosubsts = -1;
	tok_str_new (&macro_str1);
	for (ptr = macro_str;;) {
		TOK_GET (&tok, &ptr, &tokc);
		if (tok == 0) {
			break;
		}
		if (tok == TOK_TWOSHARPS) {
			continue;
		}
		if (tok == TOK_NOSUBST && start_of_nosubsts < 0) {
			start_of_nosubsts = macro_str1.len;
		}
		while (*ptr == TOK_TWOSHARPS) {
			/* given 'a##b', remove nosubsts preceding 'a' */
			if (start_of_nosubsts >= 0) {
				macro_str1.len = start_of_nosubsts;
			}
			/* given 'a##b', skip '##' */
			t = *++ptr;
			/* given 'a##b', remove nosubsts preceding 'b' */
			while (t == TOK_NOSUBST)
				t = *++ptr;
			if (t && t != TOK_TWOSHARPS) {
				CValue cval;
				TOK_GET (&t, &ptr, &cval);
				/* We concatenate the two tokens */
				cstr_new (&cstr);
				cstr_cat (&cstr, get_tok_str (tok, &tokc));
				n = cstr.size;
				cstr_cat (&cstr, get_tok_str (t, &cval));
				cstr_ccat (&cstr, '\0');

				tcc_open_bf (tcc_state, ":paste:", cstr.size);
				memcpy (file->buffer, cstr.data, cstr.size);
				while (tcc_nerr () == 0) {
					next_nomacro1 ();
					if (0 == *file->buf_ptr) {
						break;
					}
					tok_str_add2 (&macro_str1, tok, &tokc);
					tcc_warning ("pasting \"%.*s\" and \"%s\" does not give a valid preprocessing token",
						n, (char *) cstr.data, (char *) cstr.data + n);
				}
				tcc_close ();
				cstr_free (&cstr);
			}
		}
		if (tok != TOK_NOSUBST) {
			start_of_nosubsts = -1;
		}
		tok_str_add2 (&macro_str1, tok, &tokc);
	}
	tok_str_add (&macro_str1, 0);
	return macro_str1.str;
}