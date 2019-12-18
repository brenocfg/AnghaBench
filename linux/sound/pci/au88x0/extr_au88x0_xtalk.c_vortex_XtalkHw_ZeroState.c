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
 int /*<<< orphan*/  alXtalkDlineZeros ; 
 int /*<<< orphan*/  asXtalkCoefsZeros ; 
 int /*<<< orphan*/  asXtalkGainsZeros ; 
 int /*<<< orphan*/  asXtalkInStateZeros ; 
 int /*<<< orphan*/  asXtalkOutStateZeros ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetDelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetGains (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftDline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftEQStates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftXTStates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightDline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightEQStates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightXTStates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_ZeroIO (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vortex_XtalkHw_ZeroState(vortex_t * vortex)
{
	vortex_XtalkHw_ZeroIO(vortex);	// inlined

	vortex_XtalkHw_SetLeftEQ(vortex, 0, 0, asXtalkCoefsZeros);
	vortex_XtalkHw_SetRightEQ(vortex, 0, 0, asXtalkCoefsZeros);

	vortex_XtalkHw_SetLeftXT(vortex, 0, 0, asXtalkCoefsZeros);
	vortex_XtalkHw_SetRightXT(vortex, 0, 0, asXtalkCoefsZeros);

	vortex_XtalkHw_SetGains(vortex, asXtalkGainsZeros);	// inlined

	vortex_XtalkHw_SetDelay(vortex, 0, 0);	// inlined

	vortex_XtalkHw_SetLeftDline(vortex, alXtalkDlineZeros);	// inlined
	vortex_XtalkHw_SetRightDline(vortex, alXtalkDlineZeros);	// inlined
	vortex_XtalkHw_SetLeftDline(vortex, alXtalkDlineZeros);	// inlined
	vortex_XtalkHw_SetRightDline(vortex, alXtalkDlineZeros);	// inlined

	vortex_XtalkHw_SetLeftEQStates(vortex, asXtalkInStateZeros,
				       asXtalkOutStateZeros);
	vortex_XtalkHw_SetRightEQStates(vortex, asXtalkInStateZeros,
					asXtalkOutStateZeros);
	vortex_XtalkHw_SetLeftXTStates(vortex, asXtalkInStateZeros,
				       asXtalkOutStateZeros);
	vortex_XtalkHw_SetRightXTStates(vortex, asXtalkInStateZeros,
					asXtalkOutStateZeros);
}