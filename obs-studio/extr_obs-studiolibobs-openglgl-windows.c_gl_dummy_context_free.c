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
struct dummy_context {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dummy_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gl_dummy_context_free(struct dummy_context *dummy)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(dummy->hrc);
	DestroyWindow(dummy->hwnd);
	memset(dummy, 0, sizeof(struct dummy_context));
}