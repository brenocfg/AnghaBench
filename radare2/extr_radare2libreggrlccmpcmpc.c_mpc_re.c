#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * output; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ mpc_result_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;
typedef  int /*<<< orphan*/  (* mpc_dtor_t ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * mpc_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/ * mpc_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_brackets (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/ * mpc_char (char) ; 
 int /*<<< orphan*/  mpc_cleanup (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_define (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mpc_delete ; 
 int /*<<< orphan*/  mpc_err_delete (int /*<<< orphan*/ ) ; 
 char* mpc_err_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_escape () ; 
 int /*<<< orphan*/ * mpc_failf (char*,char*) ; 
 int /*<<< orphan*/  mpc_int () ; 
 int /*<<< orphan*/ * mpc_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_maybe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_new (char*) ; 
 int /*<<< orphan*/ * mpc_noneof (char*) ; 
 int /*<<< orphan*/  mpc_optimise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_or (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  mpc_parens (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  mpc_parse (char*,char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_pass () ; 
 int /*<<< orphan*/  mpc_predictive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_squares (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/ * mpc_whole (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  mpcf_re_and ; 
 int /*<<< orphan*/  mpcf_re_escape ; 
 int /*<<< orphan*/  mpcf_re_or ; 
 int /*<<< orphan*/  mpcf_re_range ; 
 int /*<<< orphan*/  mpcf_re_repeat ; 
 int /*<<< orphan*/  mpcf_snd_free ; 
 int /*<<< orphan*/  mpcf_strfold ; 

mpc_parser_t *mpc_re(const char *re) {
  
  char *err_msg;
  mpc_parser_t *err_out;
  mpc_result_t r;
  mpc_parser_t *Regex, *Term, *Factor, *Base, *Range, *RegexEnclose; 
  
  Regex  = mpc_new("regex");
  Term   = mpc_new("term");
  Factor = mpc_new("factor");
  Base   = mpc_new("base");
  Range  = mpc_new("range");
  
  mpc_define(Regex, mpc_and(2, mpcf_re_or,
    Term, 
    mpc_maybe(mpc_and(2, mpcf_snd_free, mpc_char('|'), Regex, free)),
    (mpc_dtor_t)mpc_delete
  ));
  
  mpc_define(Term, mpc_many(mpcf_re_and, Factor));
  
  mpc_define(Factor, mpc_and(2, mpcf_re_repeat,
    Base,
    mpc_or(5,
      mpc_char('*'), mpc_char('+'), mpc_char('?'),
      mpc_brackets(mpc_int(), free),
      mpc_pass()),
    (mpc_dtor_t)mpc_delete
  ));
  
  mpc_define(Base, mpc_or(4,
    mpc_parens(Regex, (mpc_dtor_t)mpc_delete),
    mpc_squares(Range, (mpc_dtor_t)mpc_delete),
    mpc_apply(mpc_escape(), mpcf_re_escape),
    mpc_apply(mpc_noneof(")|"), mpcf_re_escape)
  ));
  
  mpc_define(Range, mpc_apply(
    mpc_many(mpcf_strfold, mpc_or(2, mpc_escape(), mpc_noneof("]"))),
    mpcf_re_range
  ));
  
  RegexEnclose = mpc_whole(mpc_predictive(Regex), (mpc_dtor_t)mpc_delete);
  
  mpc_optimise(RegexEnclose);
  mpc_optimise(Regex);
  mpc_optimise(Term);
  mpc_optimise(Factor);
  mpc_optimise(Base);
  mpc_optimise(Range);
  
  if(!mpc_parse("<mpc_re_compiler>", re, RegexEnclose, &r)) {
    err_msg = mpc_err_string(r.error);
    err_out = mpc_failf("Invalid Regex: %s", err_msg);
    mpc_err_delete(r.error);  
    free(err_msg);
    r.output = err_out;
  }
  
  mpc_cleanup(6, RegexEnclose, Regex, Term, Factor, Base, Range);
  
  mpc_optimise(r.output);
  
  return r.output;
  
}