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
struct vo_x11_state {int /*<<< orphan*/  display; } ;
struct vo {struct vo_x11_state* x11; struct mp_vo_opts* opts; } ;
struct mp_vo_opts {char* winname; } ;
struct TYPE_3__ {char* res_name; char* res_class; } ;
typedef  TYPE_1__ XClassHint ;
typedef  int /*<<< orphan*/  Window ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XSetClassHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _NET_WM_PID ; 
 long getpid () ; 

__attribute__((used)) static void vo_x11_classhint(struct vo *vo, Window window, const char *name)
{
    struct mp_vo_opts *opts = vo->opts;
    struct vo_x11_state *x11 = vo->x11;
    XClassHint wmClass;
    long pid = getpid();

    wmClass.res_name = opts->winname ? opts->winname : (char *)name;
    wmClass.res_class = "mpv";
    XSetClassHint(x11->display, window, &wmClass);
    XChangeProperty(x11->display, window, XA(x11, _NET_WM_PID), XA_CARDINAL,
                    32, PropModeReplace, (unsigned char *) &pid, 1);
}