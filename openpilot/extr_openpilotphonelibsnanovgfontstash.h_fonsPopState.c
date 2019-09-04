#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nstates; int /*<<< orphan*/  errorUptr; int /*<<< orphan*/  (* handleError ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ FONScontext ;

/* Variables and functions */
 int /*<<< orphan*/  FONS_STATES_UNDERFLOW ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fonsPopState(FONScontext* stash)
{
	if (stash->nstates <= 1) {
		if (stash->handleError)
			stash->handleError(stash->errorUptr, FONS_STATES_UNDERFLOW, 0);
		return;
	}
	stash->nstates--;
}