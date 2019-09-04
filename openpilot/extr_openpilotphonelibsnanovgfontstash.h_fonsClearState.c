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
struct TYPE_3__ {float size; int color; int align; scalar_t__ spacing; scalar_t__ blur; scalar_t__ font; } ;
typedef  TYPE_1__ FONSstate ;
typedef  int /*<<< orphan*/  FONScontext ;

/* Variables and functions */
 int FONS_ALIGN_BASELINE ; 
 int FONS_ALIGN_LEFT ; 
 TYPE_1__* fons__getState (int /*<<< orphan*/ *) ; 

void fonsClearState(FONScontext* stash)
{
	FONSstate* state = fons__getState(stash);
	state->size = 12.0f;
	state->color = 0xffffffff;
	state->font = 0;
	state->blur = 0;
	state->spacing = 0;
	state->align = FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE;
}