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
struct nvidia_par {int dummy; } ;
struct _riva_hw_state {int /*<<< orphan*/ * seq; int /*<<< orphan*/ * gra; int /*<<< orphan*/ * attr; int /*<<< orphan*/ * crtc; int /*<<< orphan*/  misc_output; } ;

/* Variables and functions */
 int NUM_ATC_REGS ; 
 int NUM_CRT_REGS ; 
 int NUM_GRC_REGS ; 
 int NUM_SEQ_REGS ; 
 int /*<<< orphan*/  NVLockUnlock (struct nvidia_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVReadAttr (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVReadCrtc (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVReadGr (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVReadMiscOut (struct nvidia_par*) ; 
 int /*<<< orphan*/  NVReadSeq (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  NVUnloadStateExt (struct nvidia_par*,struct _riva_hw_state*) ; 

__attribute__((used)) static void nvidia_save_vga(struct nvidia_par *par,
			    struct _riva_hw_state *state)
{
	int i;

	NVTRACE_ENTER();
	NVLockUnlock(par, 0);

	NVUnloadStateExt(par, state);

	state->misc_output = NVReadMiscOut(par);

	for (i = 0; i < NUM_CRT_REGS; i++)
		state->crtc[i] = NVReadCrtc(par, i);

	for (i = 0; i < NUM_ATC_REGS; i++)
		state->attr[i] = NVReadAttr(par, i);

	for (i = 0; i < NUM_GRC_REGS; i++)
		state->gra[i] = NVReadGr(par, i);

	for (i = 0; i < NUM_SEQ_REGS; i++)
		state->seq[i] = NVReadSeq(par, i);
	NVTRACE_LEAVE();
}