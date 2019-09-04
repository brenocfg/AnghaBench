#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned short xt_mode; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
#define  XT_DIAMOND 131 
#define  XT_HEADPHONE 130 
#define  XT_SPEAKER0 129 
#define  XT_SPEAKER1 128 
 int /*<<< orphan*/  vortex_XtalkHw_Enable (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_XtalkHw_ProgramDiamondXtalk (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_XtalkHw_ProgramPipe (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_XtalkHw_ProgramXtalkNarrow (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_XtalkHw_ProgramXtalkWide (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetGainsAllChan (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetSampleRate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vortex_XtalkHw_init (TYPE_1__*) ; 

__attribute__((used)) static int Vort3DRend_Initialize(vortex_t * v, unsigned short mode)
{
	v->xt_mode = mode;	/* this_14 */

	vortex_XtalkHw_init(v);
	vortex_XtalkHw_SetGainsAllChan(v);
	switch (v->xt_mode) {
	case XT_SPEAKER0:
		vortex_XtalkHw_ProgramXtalkNarrow(v);
		break;
	case XT_SPEAKER1:
		vortex_XtalkHw_ProgramXtalkWide(v);
		break;
	default:
	case XT_HEADPHONE:
		vortex_XtalkHw_ProgramPipe(v);
		break;
	case XT_DIAMOND:
		vortex_XtalkHw_ProgramDiamondXtalk(v);
		break;
	}
	vortex_XtalkHw_SetSampleRate(v, 0x11);
	vortex_XtalkHw_Enable(v);
	return 0;
}