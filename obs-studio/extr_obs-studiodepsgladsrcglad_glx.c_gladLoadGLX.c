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
typedef  int /*<<< orphan*/  GLADloadproc ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  close_gl () ; 
 scalar_t__ get_proc ; 
 int /*<<< orphan*/  gladLoadGLXLoader (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ open_gl () ; 

int gladLoadGLX(Display *dpy, int screen) {
    if(open_gl()) {
        gladLoadGLXLoader((GLADloadproc)get_proc, dpy, screen);
        close_gl();
        return 1;
    }

    return 0;
}