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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  mt19937_state ;

/* Variables and functions */
 int mt19937_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint64_t mt19937_next64(mt19937_state *state) {
  return (uint64_t)mt19937_next(state) << 32 | mt19937_next(state);
}