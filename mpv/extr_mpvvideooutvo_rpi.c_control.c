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
typedef  int uint32_t ;
struct vo {int want_redraw; struct priv* priv; } ;
struct priv {int reload_display; double display_fps; int /*<<< orphan*/  display_mutex; int /*<<< orphan*/  renderer_enabled; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
#define  VOCTRL_CHECK_EVENTS 133 
#define  VOCTRL_FULLSCREEN 132 
#define  VOCTRL_GET_DISPLAY_FPS 131 
#define  VOCTRL_REDRAW_FRAME 130 
#define  VOCTRL_SCREENSHOT_WIN 129 
#define  VOCTRL_SET_PANSCAN 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recreate_renderer (struct vo*) ; 
 int /*<<< orphan*/  resize (struct vo*) ; 
 int /*<<< orphan*/  set_geometry (struct vo*) ; 
 struct mp_image* take_screenshot (struct vo*) ; 
 int /*<<< orphan*/  update_osd (struct vo*) ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *data)
{
    struct priv *p = vo->priv;

    switch (request) {
    case VOCTRL_FULLSCREEN:
        if (p->renderer_enabled)
            set_geometry(vo);
        vo->want_redraw = true;
        return VO_TRUE;
    case VOCTRL_SET_PANSCAN:
        if (p->renderer_enabled)
            resize(vo);
        vo->want_redraw = true;
        return VO_TRUE;
    case VOCTRL_REDRAW_FRAME:
        update_osd(vo);
        return VO_TRUE;
    case VOCTRL_SCREENSHOT_WIN:
        *(struct mp_image **)data = take_screenshot(vo);
        return VO_TRUE;
    case VOCTRL_CHECK_EVENTS: {
        pthread_mutex_lock(&p->display_mutex);
        bool reload_required = p->reload_display;
        p->reload_display = false;
        pthread_mutex_unlock(&p->display_mutex);
        if (reload_required)
            recreate_renderer(vo);
        return VO_TRUE;
    }
    case VOCTRL_GET_DISPLAY_FPS:
        *(double *)data = p->display_fps;
        return VO_TRUE;
    }

    return VO_NOTIMPL;
}