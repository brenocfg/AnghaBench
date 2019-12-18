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
struct vo {TYPE_1__* opts; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  window; scalar_t__ switch_mode; } ;
typedef  int Uint32 ;
struct TYPE_2__ {int fullscreen; } ;
typedef  int /*<<< orphan*/  SDL_bool ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int SDL_GetWindowFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_IsScreenSaverEnabled () ; 
 scalar_t__ SDL_SetWindowFullscreen (int /*<<< orphan*/ ,int) ; 
 int SDL_WINDOW_FULLSCREEN ; 
 int SDL_WINDOW_FULLSCREEN_DESKTOP ; 
 int /*<<< orphan*/  force_resize (struct vo*) ; 
 int /*<<< orphan*/  set_screensaver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_fullscreen(struct vo *vo)
{
    struct priv *vc = vo->priv;
    int fs = vo->opts->fullscreen;
    SDL_bool prev_screensaver_state = SDL_IsScreenSaverEnabled();

    Uint32 fs_flag;
    if (vc->switch_mode)
        fs_flag = SDL_WINDOW_FULLSCREEN;
    else
        fs_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;

    Uint32 old_flags = SDL_GetWindowFlags(vc->window);
    int prev_fs = !!(old_flags & fs_flag);
    if (fs == prev_fs)
        return;

    Uint32 flags = 0;
    if (fs)
        flags |= fs_flag;

    if (SDL_SetWindowFullscreen(vc->window, flags)) {
        MP_ERR(vo, "SDL_SetWindowFullscreen failed\n");
        return;
    }

    // toggling fullscreen might recreate the window, so better guard for this
    set_screensaver(prev_screensaver_state);

    force_resize(vo);
}