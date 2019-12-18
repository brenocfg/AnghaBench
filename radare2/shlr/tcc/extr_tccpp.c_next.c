#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct macro_level {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_2__ TokenString ;
struct TYPE_9__ {TYPE_1__* cstr; } ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int PARSE_FLAG_PREPROCESS ; 
 int PARSE_FLAG_SPACES ; 
 int PARSE_FLAG_TOK_NUM ; 
 scalar_t__ TOK_IDENT ; 
 scalar_t__ TOK_NOSUBST ; 
 scalar_t__ TOK_PPNUM ; 
 int /*<<< orphan*/ * define_find (scalar_t__) ; 
 int /*<<< orphan*/ * macro_ptr ; 
 int /*<<< orphan*/ * macro_ptr_allocated ; 
 scalar_t__ macro_subst_tok (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct macro_level**) ; 
 int /*<<< orphan*/  next_nomacro () ; 
 int /*<<< orphan*/  next_nomacro_spc () ; 
 int parse_flags ; 
 int /*<<< orphan*/  parse_number (char*) ; 
 scalar_t__ tok ; 
 int /*<<< orphan*/  tok_str_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok_str_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok_str_new (TYPE_2__*) ; 
 TYPE_3__ tokc ; 
 scalar_t__ unget_buffer_enabled ; 
 int /*<<< orphan*/ * unget_saved_macro_ptr ; 

void next(void)
{
	Sym *nested_list, *s;
	TokenString str;
	struct macro_level *ml;

redo:
	if (parse_flags & PARSE_FLAG_SPACES) {
		next_nomacro_spc ();
	} else {
		next_nomacro ();
	}
	if (!macro_ptr) {
		/* if not reading from macro substituted string, then try
		   to substitute macros */
		if (tok >= TOK_IDENT &&
		    (parse_flags & PARSE_FLAG_PREPROCESS)) {
			s = define_find (tok);
			if (s) {
				/* we have a macro: we try to substitute */
				tok_str_new (&str);
				nested_list = NULL;
				ml = NULL;
				if (macro_subst_tok (&str, &nested_list, s, &ml) == 0) {
					/* substitution done, NOTE: maybe empty */
					tok_str_add (&str, 0);
					macro_ptr = str.str;
					macro_ptr_allocated = str.str;
					goto redo;
				}
			}
		}
	} else {
		if (tok == 0) {
			/* end of macro or end of unget buffer */
			if (unget_buffer_enabled) {
				macro_ptr = unget_saved_macro_ptr;
				unget_buffer_enabled = 0;
			} else {
				/* end of macro string: free it */
				tok_str_free (macro_ptr_allocated);
				macro_ptr_allocated = NULL;
				macro_ptr = NULL;
			}
			goto redo;
		} else if (tok == TOK_NOSUBST) {
			/* discard preprocessor's nosubst markers */
			goto redo;
		}
	}

	/* convert preprocessor tokens into C tokens */
	if (tok == TOK_PPNUM &&
	    (parse_flags & PARSE_FLAG_TOK_NUM)) {
		parse_number ((char *) tokc.cstr->data);
	}
}