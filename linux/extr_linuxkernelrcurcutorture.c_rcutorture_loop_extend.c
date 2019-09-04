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
struct torture_random_state {int dummy; } ;

/* Variables and functions */
 int RCUTORTURE_RDR_MAX_LOOPS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int rcutorture_extend_mask (int,struct torture_random_state*) ; 
 int rcutorture_extend_mask_max () ; 
 int /*<<< orphan*/  rcutorture_one_extend (int*,int,struct torture_random_state*) ; 
 int torture_random (struct torture_random_state*) ; 

__attribute__((used)) static void rcutorture_loop_extend(int *readstate,
				   struct torture_random_state *trsp)
{
	int i;
	int mask = rcutorture_extend_mask_max();

	WARN_ON_ONCE(!*readstate); /* -Existing- RCU read-side critsect! */
	if (!((mask - 1) & mask))
		return;  /* Current RCU flavor not extendable. */
	i = (torture_random(trsp) >> 3) & RCUTORTURE_RDR_MAX_LOOPS;
	while (i--) {
		mask = rcutorture_extend_mask(*readstate, trsp);
		rcutorture_one_extend(readstate, mask, trsp);
	}
}