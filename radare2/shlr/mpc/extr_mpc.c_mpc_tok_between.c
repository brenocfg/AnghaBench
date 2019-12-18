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
typedef  int /*<<< orphan*/  mpc_dtor_t ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * mpc_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_sym (char const*) ; 
 int /*<<< orphan*/  mpc_tok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpcf_snd_free ; 

mpc_parser_t *mpc_tok_between(mpc_parser_t *a, mpc_dtor_t ad, const char *o, const char *c) {
  return mpc_and(3, mpcf_snd_free,
    mpc_sym(o), mpc_tok(a), mpc_sym(c),
    free, ad);
}