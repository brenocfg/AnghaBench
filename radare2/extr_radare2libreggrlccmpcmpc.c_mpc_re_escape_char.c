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
typedef  int /*<<< orphan*/  mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * mpc_alphanum () ; 
 int /*<<< orphan*/ * mpc_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_boundary () ; 
 int /*<<< orphan*/ * mpc_char (char) ; 
 int /*<<< orphan*/ * mpc_digit () ; 
 int /*<<< orphan*/ * mpc_eoi () ; 
 int /*<<< orphan*/  mpc_lift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_not_lift (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_soi () ; 
 int /*<<< orphan*/ * mpc_whitespace () ; 
 int /*<<< orphan*/  mpcf_ctor_str ; 
 int /*<<< orphan*/  mpcf_snd ; 

__attribute__((used)) static mpc_parser_t *mpc_re_escape_char(char c) {
  switch (c) {
    case 'a': return mpc_char('\a');
    case 'f': return mpc_char('\f');
    case 'n': return mpc_char('\n');
    case 'r': return mpc_char('\r');
    case 't': return mpc_char('\t');
    case 'v': return mpc_char('\v');
    case 'b': return mpc_and(2, mpcf_snd, mpc_boundary(), mpc_lift(mpcf_ctor_str), free);
    case 'B': return mpc_not_lift(mpc_boundary(), free, mpcf_ctor_str);
    case 'A': return mpc_and(2, mpcf_snd, mpc_soi(), mpc_lift(mpcf_ctor_str), free);
    case 'Z': return mpc_and(2, mpcf_snd, mpc_eoi(), mpc_lift(mpcf_ctor_str), free);
    case 'd': return mpc_digit();
    case 'D': return mpc_not_lift(mpc_digit(), free, mpcf_ctor_str);
    case 's': return mpc_whitespace();
    case 'S': return mpc_not_lift(mpc_whitespace(), free, mpcf_ctor_str);
    case 'w': return mpc_alphanum();
    case 'W': return mpc_not_lift(mpc_alphanum(), free, mpcf_ctor_str);
    default: return NULL;
  }
}