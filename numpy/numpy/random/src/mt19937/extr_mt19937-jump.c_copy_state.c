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
struct TYPE_4__ {int /*<<< orphan*/  pos; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ mt19937_state ;

/* Variables and functions */
 int N ; 

void copy_state(mt19937_state *target_state, mt19937_state *state) {
  int i;

  for (i = 0; i < N; i++)
    target_state->key[i] = state->key[i];

  target_state->pos = state->pos;
}