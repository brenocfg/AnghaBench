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
typedef  char mpc_val_t ;
typedef  char mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* mpc_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*)) ; 
 char* mpc_any () ; 
 char* mpc_char (char) ; 
 int /*<<< orphan*/  mpc_eoi () ; 
 int /*<<< orphan*/  mpc_lift (int /*<<< orphan*/ ) ; 
 char* mpc_re_escape_char (char) ; 
 int /*<<< orphan*/  mpc_soi () ; 
 int /*<<< orphan*/  mpcf_ctor_str ; 
 int /*<<< orphan*/  mpcf_snd ; 

__attribute__((used)) static mpc_val_t *mpcf_re_escape(mpc_val_t *x) {
  
  char *s = x;
  mpc_parser_t *p;
  
  /* Regex Special Characters */
  if (s[0] == '.') { free(s); return mpc_any(); }
  if (s[0] == '^') { free(s); return mpc_and(2, mpcf_snd, mpc_soi(), mpc_lift(mpcf_ctor_str), free); }
  if (s[0] == '$') { free(s); return mpc_and(2, mpcf_snd, mpc_eoi(), mpc_lift(mpcf_ctor_str), free); }
  
  /* Regex Escape */
  if (s[0] == '\\') {
    p = mpc_re_escape_char(s[1]);
    p = (!p) ? mpc_char(s[1]) : p;
    free(s);
    return p;
  }
  
  /* Regex Standard */
  p = mpc_char(s[0]);
  free(s);
  return p;
}