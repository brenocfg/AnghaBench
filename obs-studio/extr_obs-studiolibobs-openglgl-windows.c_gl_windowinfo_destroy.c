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
struct gl_windowinfo {scalar_t__ hdc; int /*<<< orphan*/  hwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bfree (struct gl_windowinfo*) ; 

void gl_windowinfo_destroy(struct gl_windowinfo *wi)
{
	if (wi) {
		if (wi->hdc)
			ReleaseDC(wi->hwnd, wi->hdc);
		bfree(wi);
	}
}