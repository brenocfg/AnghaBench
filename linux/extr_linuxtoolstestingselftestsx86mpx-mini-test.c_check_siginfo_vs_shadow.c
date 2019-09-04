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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 size_t NR_MPX_BOUNDS_REGISTERS ; 
 void* __si_bounds_lower (int /*<<< orphan*/ *) ; 
 void* __si_bounds_upper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t expected_bnd_index ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__** shadow_plb ; 
 int /*<<< orphan*/  stderr ; 

void check_siginfo_vs_shadow(siginfo_t* si)
{
	int siginfo_ok = 1;
	void *shadow_lower = (void *)(unsigned long)shadow_plb[expected_bnd_index][0];
	void *shadow_upper = (void *)(unsigned long)shadow_plb[expected_bnd_index][1];

	if ((expected_bnd_index < 0) ||
	    (expected_bnd_index >= NR_MPX_BOUNDS_REGISTERS)) {
		fprintf(stderr, "ERROR: invalid expected_bnd_index: %d\n",
			expected_bnd_index);
		exit(6);
	}
	if (__si_bounds_lower(si) != shadow_lower)
		siginfo_ok = 0;
	if (__si_bounds_upper(si) != shadow_upper)
		siginfo_ok = 0;

	if (!siginfo_ok) {
		fprintf(stderr, "ERROR: siginfo bounds do not match "
			"shadow bounds for register %d\n", expected_bnd_index);
		exit(7);
	}
}