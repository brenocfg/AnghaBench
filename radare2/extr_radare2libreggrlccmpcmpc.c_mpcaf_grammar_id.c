#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpca_grammar_st_t ;
typedef  int /*<<< orphan*/  mpc_val_t ;
struct TYPE_6__ {scalar_t__ name; } ;
typedef  TYPE_1__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mpca_add_tag (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* mpca_grammar_find_parser (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpca_root (TYPE_1__*) ; 
 int /*<<< orphan*/ * mpca_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mpc_val_t *mpcaf_grammar_id(mpc_val_t *x, void *s) {
  
  mpca_grammar_st_t *st = s;
  mpc_parser_t *p = mpca_grammar_find_parser(x, st);
  free(x);

  if (p->name) {
    return mpca_state(mpca_root(mpca_add_tag(p, p->name)));
  } else {
    return mpca_state(mpca_root(p));
  }
}