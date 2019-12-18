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
struct TYPE_6__ {int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ state_t ;
typedef  int /*<<< orphan*/  (* round_trip_t ) (TYPE_1__*) ;

/* Variables and functions */
 scalar_t__ FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void state_randomRoundTrip(state_t* state, round_trip_t rt0,
                                  round_trip_t rt1)
{
    if (FUZZ_rand32(&state->seed, 0, 1)) {
      rt0(state);
    } else {
      rt1(state);
    }
}