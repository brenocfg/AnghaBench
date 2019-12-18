#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pos; } ;
typedef  TYPE_1__ mt19937_state ;

/* Variables and functions */
 int MEXP ; 
 scalar_t__ N ; 
 int /*<<< orphan*/  P_SIZE ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 int /*<<< orphan*/  horner1 (unsigned long*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_coef (unsigned long*,int,int) ; 

void mt19937_jump_state(mt19937_state *state, const char *jump_str) {
  unsigned long *pf;
  int i;

  pf = (unsigned long *)calloc(P_SIZE, sizeof(unsigned long));

  for (i = MEXP - 1; i > -1; i--) {
    if (jump_str[i] == '1')
      set_coef(pf, i, 1);
  }
  /* TODO: Should generate the next set and start from 0, but doesn't matter ??
   */
  if (state->pos >= N) {
    state->pos = 0;
  }

  horner1(pf, state);

  free(pf);
}