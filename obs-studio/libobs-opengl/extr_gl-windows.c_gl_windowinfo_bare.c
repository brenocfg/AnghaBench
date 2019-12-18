#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hwnd; } ;
struct gs_init_data {TYPE_1__ window; } ;
struct gl_windowinfo {int /*<<< orphan*/  hdc; int /*<<< orphan*/  hwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  bfree (struct gl_windowinfo*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct gl_windowinfo* bzalloc (int) ; 

__attribute__((used)) static struct gl_windowinfo *gl_windowinfo_bare(const struct gs_init_data *info)
{
	struct gl_windowinfo *wi = bzalloc(sizeof(struct gl_windowinfo));
	wi->hwnd = info->window.hwnd;
	wi->hdc = GetDC(wi->hwnd);

	if (!wi->hdc) {
		blog(LOG_ERROR, "Unable to get device context from window");
		bfree(wi);
		return NULL;
	}

	return wi;
}