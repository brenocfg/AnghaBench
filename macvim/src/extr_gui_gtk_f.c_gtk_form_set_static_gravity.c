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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GdkWindow ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_window_set_static_gravities (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gtk_form_set_static_gravity(GdkWindow *window, gboolean use_static)
{
    /* We don't check if static gravity is actually supported, because it
     * results in an annoying assertion error message. */
    gdk_window_set_static_gravities(window, use_static);
}