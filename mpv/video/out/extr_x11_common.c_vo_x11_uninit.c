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
struct vo_x11_state {scalar_t__ window; scalar_t__ rootwin; scalar_t__ colormap; scalar_t__* wakeup_pipe; int /*<<< orphan*/  screensaver_sem; int /*<<< orphan*/  screensaver_thread; int /*<<< orphan*/  screensaver_terminate; scalar_t__ screensaver_thread_running; scalar_t__ display; scalar_t__ xim; scalar_t__ xic; int /*<<< orphan*/  input_ctx; } ;
struct vo {struct vo_x11_state* x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct vo_x11_state*,char*) ; 
 int /*<<< orphan*/  MP_INPUT_RELEASE_ALL ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  XCloseDisplay (scalar_t__) ; 
 int /*<<< orphan*/  XCloseIM (scalar_t__) ; 
 int /*<<< orphan*/  XDestroyIC (scalar_t__) ; 
 int /*<<< orphan*/  XDestroyWindow (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XFreeColormap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XSetErrorHandler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XUnmapWindow (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_screensaver (struct vo_x11_state*,int) ; 
 int /*<<< orphan*/  talloc_free (struct vo_x11_state*) ; 
 int /*<<< orphan*/ * x11_error_output ; 

void vo_x11_uninit(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;
    if (!x11)
        return;

    mp_input_put_key(x11->input_ctx, MP_INPUT_RELEASE_ALL);

    set_screensaver(x11, true);

    if (x11->window != None && x11->window != x11->rootwin) {
        XUnmapWindow(x11->display, x11->window);
        XDestroyWindow(x11->display, x11->window);
    }
    if (x11->xic)
        XDestroyIC(x11->xic);
    if (x11->colormap != None)
        XFreeColormap(vo->x11->display, x11->colormap);

    MP_DBG(x11, "uninit ...\n");
    if (x11->xim)
        XCloseIM(x11->xim);
    if (x11->display) {
        XSetErrorHandler(NULL);
        x11_error_output = NULL;
        XCloseDisplay(x11->display);
    }

    if (x11->screensaver_thread_running) {
        atomic_store(&x11->screensaver_terminate, true);
        sem_post(&x11->screensaver_sem);
        pthread_join(x11->screensaver_thread, NULL);
        sem_destroy(&x11->screensaver_sem);
    }

    if (x11->wakeup_pipe[0] >= 0) {
        close(x11->wakeup_pipe[0]);
        close(x11->wakeup_pipe[1]);
    }

    talloc_free(x11);
    vo->x11 = NULL;
}