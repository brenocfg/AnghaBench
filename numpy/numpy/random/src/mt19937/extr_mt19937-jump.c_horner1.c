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
typedef  int /*<<< orphan*/  mt19937_state ;

/* Variables and functions */
 int MEXP ; 
 int /*<<< orphan*/  add_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  copy_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_next (int /*<<< orphan*/ *) ; 
 scalar_t__ get_coef (unsigned long*,int) ; 

void horner1(unsigned long *pf, mt19937_state *state) {
  int i = MEXP - 1;
  mt19937_state *temp;

  temp = (mt19937_state *)calloc(1, sizeof(mt19937_state));

  while (get_coef(pf, i) == 0)
    i--;

  if (i > 0) {
    copy_state(temp, state);
    gen_next(temp);
    i--;
    for (; i > 0; i--) {
      if (get_coef(pf, i) != 0)
        add_state(temp, state);
      else
        ;
      gen_next(temp);
    }
    if (get_coef(pf, 0) != 0)
      add_state(temp, state);
    else
      ;
  } else if (i == 0)
    copy_state(temp, state);
  else
    ;

  copy_state(state, temp);
  free(temp);
}