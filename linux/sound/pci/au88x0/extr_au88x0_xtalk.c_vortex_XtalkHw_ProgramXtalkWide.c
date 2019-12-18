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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  asXtalkWideCoefsLeftEq ; 
 int /*<<< orphan*/  asXtalkWideCoefsLeftXt ; 
 int /*<<< orphan*/  asXtalkWideCoefsRightEq ; 
 int /*<<< orphan*/  sXtalkWideKLeftEq ; 
 int /*<<< orphan*/  sXtalkWideKLeftXt ; 
 int /*<<< orphan*/  sXtalkWideKRightEq ; 
 int /*<<< orphan*/  sXtalkWideShiftLeftEq ; 
 int /*<<< orphan*/  sXtalkWideShiftLeftXt ; 
 int /*<<< orphan*/  sXtalkWideShiftRightEq ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetDelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wXtalkWideLeftDelay ; 
 int /*<<< orphan*/  wXtalkWideRightDelay ; 

__attribute__((used)) static void vortex_XtalkHw_ProgramXtalkWide(vortex_t * vortex)
{

	vortex_XtalkHw_SetLeftEQ(vortex, sXtalkWideKLeftEq,
				 sXtalkWideShiftLeftEq, asXtalkWideCoefsLeftEq);
	vortex_XtalkHw_SetRightEQ(vortex, sXtalkWideKRightEq,
				  sXtalkWideShiftRightEq,
				  asXtalkWideCoefsRightEq);
	vortex_XtalkHw_SetLeftXT(vortex, sXtalkWideKLeftXt,
				 sXtalkWideShiftLeftXt, asXtalkWideCoefsLeftXt);
	vortex_XtalkHw_SetRightXT(vortex, sXtalkWideKLeftXt,
				  sXtalkWideShiftLeftXt,
				  asXtalkWideCoefsLeftXt);

	vortex_XtalkHw_SetDelay(vortex, wXtalkWideRightDelay, wXtalkWideLeftDelay);	// inlined
}