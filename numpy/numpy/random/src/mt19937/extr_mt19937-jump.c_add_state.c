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
struct TYPE_4__ {int pos; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ mt19937_state ;

/* Variables and functions */
 int N ; 

void add_state(mt19937_state *state1, mt19937_state *state2) {
  int i, pt1 = state1->pos, pt2 = state2->pos;

  if (pt2 - pt1 >= 0) {
    for (i = 0; i < N - pt2; i++)
      state1->key[i + pt1] ^= state2->key[i + pt2];
    for (; i < N - pt1; i++)
      state1->key[i + pt1] ^= state2->key[i + (pt2 - N)];
    for (; i < N; i++)
      state1->key[i + (pt1 - N)] ^= state2->key[i + (pt2 - N)];
  } else {
    for (i = 0; i < N - pt1; i++)
      state1->key[i + pt1] ^= state2->key[i + pt2];
    for (; i < N - pt2; i++)
      state1->key[i + (pt1 - N)] ^= state2->key[i + pt2];
    for (; i < N; i++)
      state1->key[i + (pt1 - N)] ^= state2->key[i + (pt2 - N)];
  }
}