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
struct vt_switcher {int /*<<< orphan*/  tty_fd; } ;
struct vt_mode {int /*<<< orphan*/  mode; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_SIGNAL ; 
 int /*<<< orphan*/  MP_ERR (struct vt_switcher*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELEASE_SIGNAL ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  VT_AUTO ; 
 int /*<<< orphan*/  VT_SETMODE ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  install_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vt_mode*) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vt_switcher_pipe ; 

void vt_switcher_destroy(struct vt_switcher *s)
{
    struct vt_mode vt_mode = {0};
    vt_mode.mode = VT_AUTO;
    if (ioctl(s->tty_fd, VT_SETMODE, &vt_mode) < 0) {
        MP_ERR(s, "VT_SETMODE failed: %s\n", mp_strerror(errno));
        return;
    }

    install_signal(RELEASE_SIGNAL, SIG_DFL);
    install_signal(ACQUIRE_SIGNAL, SIG_DFL);
    close(s->tty_fd);
    close(vt_switcher_pipe[0]);
    close(vt_switcher_pipe[1]);
}