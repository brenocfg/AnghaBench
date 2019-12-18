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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  pcg_state; } ;
typedef  TYPE_1__ pcg64_state ;

/* Variables and functions */
 int /*<<< orphan*/  pcg64_random_r (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t pcg64_next64(pcg64_state *state) {
  return pcg64_random_r(state->pcg_state);
}