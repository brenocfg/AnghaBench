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
typedef  int /*<<< orphan*/  XErrorEvent ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  NK_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_err ; 
 int /*<<< orphan*/  nk_true ; 

__attribute__((used)) static int gl_error_handler(Display *dpy, XErrorEvent *ev)
{NK_UNUSED(dpy); NK_UNUSED(ev); gl_err = nk_true; return 0;}