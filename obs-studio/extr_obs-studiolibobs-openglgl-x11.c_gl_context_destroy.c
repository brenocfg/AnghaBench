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
struct gl_platform {int /*<<< orphan*/  context; int /*<<< orphan*/ * display; } ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  bfree (struct gl_platform*) ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXMakeContextCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_context_destroy(struct gl_platform *plat)
{
	Display *display = plat->display;

	glXMakeContextCurrent(display, None, None, NULL);
	glXDestroyContext(display, plat->context);
	bfree(plat);
}