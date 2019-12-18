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
typedef  double int32_t ;

/* Variables and functions */
 int mt19937_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline double mt19937_next_double(mt19937_state *state) {
  int32_t a = mt19937_next(state) >> 5, b = mt19937_next(state) >> 6;
  return (a * 67108864.0 + b) / 9007199254740992.0;
}