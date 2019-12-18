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
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int bCapturaRegs ; 
 int bStep ; 
 int /*<<< orphan*/  bochs_send_cmd (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  isBochs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_debug_bochs_step(RDebug *dbg) {
	if (!isBochs (dbg)) {
		return false;
	}
	//eprintf ("bochs_step\n");
	bochs_send_cmd (desc,"s",true);
	bCapturaRegs = true;
	bStep = true;
	return true;
}