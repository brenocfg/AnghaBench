#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
typedef  TYPE_1__ mpca_grammar_st_t ;
typedef  int /*<<< orphan*/  mpc_val_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;

/* Variables and functions */
 int MPCA_LANG_WHITESPACE_SENSITIVE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mpc_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_re (char*) ; 
 int /*<<< orphan*/ * mpc_tok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpca_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpca_tag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpcf_str_ast ; 
 char* mpcf_unescape_regex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mpc_val_t *mpcaf_grammar_regex(mpc_val_t *x, void *s) {
  mpca_grammar_st_t *st = s;
  char *y = mpcf_unescape_regex(x);
  mpc_parser_t *p = (st->flags & MPCA_LANG_WHITESPACE_SENSITIVE) ? mpc_re(y) : mpc_tok(mpc_re(y));
  free(y);
  return mpca_state(mpca_tag(mpc_apply(p, mpcf_str_ast), "regex"));
}