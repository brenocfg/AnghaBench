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
typedef  scalar_t__ linenr_T ;
struct TYPE_3__ {scalar_t__ line1; scalar_t__ line2; scalar_t__ arg; } ;
typedef  TYPE_1__ exarg_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOT_VALID ; 
 scalar_t__ OK ; 
 scalar_t__ StringValuePtr (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ T_STRING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  changed () ; 
 int /*<<< orphan*/  check_cursor () ; 
 scalar_t__ ensure_ruby_initialized () ; 
 int /*<<< orphan*/  error_print (int) ; 
 int /*<<< orphan*/  eval_enc_string_protect (char*,int*) ; 
 scalar_t__ ml_get (scalar_t__) ; 
 int /*<<< orphan*/  ml_replace (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rb_lastline_get () ; 
 int /*<<< orphan*/  rb_lastline_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syn_changed (scalar_t__) ; 
 scalar_t__ u_save (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  update_curbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_str2rb_enc_str (char*) ; 

void ex_rubydo(exarg_T *eap)
{
    int state;
    linenr_T i;

    if (ensure_ruby_initialized())
    {
	if (u_save(eap->line1 - 1, eap->line2 + 1) != OK)
	    return;
	for (i = eap->line1; i <= eap->line2; i++) {
	    VALUE line;

	    line = vim_str2rb_enc_str((char *)ml_get(i));
	    rb_lastline_set(line);
	    eval_enc_string_protect((char *) eap->arg, &state);
	    if (state) {
		error_print(state);
		break;
	    }
	    line = rb_lastline_get();
	    if (!NIL_P(line)) {
		if (TYPE(line) != T_STRING) {
		    EMSG(_("E265: $_ must be an instance of String"));
		    return;
		}
		ml_replace(i, (char_u *) StringValuePtr(line), 1);
		changed();
#ifdef SYNTAX_HL
		syn_changed(i); /* recompute syntax hl. for this line */
#endif
	    }
	}
	check_cursor();
	update_curbuf(NOT_VALID);
    }
}