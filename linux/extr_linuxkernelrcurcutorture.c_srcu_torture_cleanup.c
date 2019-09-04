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
typedef  int /*<<< orphan*/  DEFINE_TORTURE_RANDOM ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_srcu_struct_quiesced (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_ctl ; 
 int /*<<< orphan*/  srcu_ctld ; 
 int /*<<< orphan*/ * srcu_ctlp ; 
 int torture_random (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void srcu_torture_cleanup(void)
{
	static DEFINE_TORTURE_RANDOM(rand);

	if (torture_random(&rand) & 0x800)
		cleanup_srcu_struct(&srcu_ctld);
	else
		cleanup_srcu_struct_quiesced(&srcu_ctld);
	srcu_ctlp = &srcu_ctl; /* In case of a later rcutorture run. */
}