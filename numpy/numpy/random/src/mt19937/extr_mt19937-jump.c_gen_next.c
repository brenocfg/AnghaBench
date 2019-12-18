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
struct TYPE_3__ {int pos; unsigned long* key; } ;
typedef  TYPE_1__ mt19937_state ;

/* Variables and functions */
 unsigned long LOWER_MASK ; 
 int M ; 
#define  MATRIX_A 128 
 int N ; 
 unsigned long UPPER_MASK ; 

void gen_next(mt19937_state *state) {
  int num;
  unsigned long y;
  static unsigned long mag02[2] = {0x0ul, MATRIX_A};

  num = state->pos;
  if (num < N - M) {
    y = (state->key[num] & UPPER_MASK) | (state->key[num + 1] & LOWER_MASK);
    state->key[num] = state->key[num + M] ^ (y >> 1) ^ mag02[y % 2];
    state->pos++;
  } else if (num < N - 1) {
    y = (state->key[num] & UPPER_MASK) | (state->key[num + 1] & LOWER_MASK);
    state->key[num] = state->key[num + (M - N)] ^ (y >> 1) ^ mag02[y % 2];
    state->pos++;
  } else if (num == N - 1) {
    y = (state->key[N - 1] & UPPER_MASK) | (state->key[0] & LOWER_MASK);
    state->key[N - 1] = state->key[M - 1] ^ (y >> 1) ^ mag02[y % 2];
    state->pos = 0;
  }
}