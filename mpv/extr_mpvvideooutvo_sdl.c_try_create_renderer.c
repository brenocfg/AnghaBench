#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct priv {int renderer_index; scalar_t__ window_title; int /*<<< orphan*/  window; TYPE_1__ renderer_info; int /*<<< orphan*/  osd_format; int /*<<< orphan*/  allow_sw; int /*<<< orphan*/  renderer; } ;
struct mp_rect {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_1__ SDL_RendererInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,...) ; 
 int /*<<< orphan*/  MP_INFO (struct vo*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateRenderer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateWindow (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ SDL_GetRenderDriverInfo (int,TYPE_1__*) ; 
 scalar_t__ SDL_GetRendererInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_SetWindowTitle (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SDL_WINDOWPOS_UNDEFINED ; 
 int SDL_WINDOW_HIDDEN ; 
 int SDL_WINDOW_RESIZABLE ; 
 int VO_WIN_FORCE_POS ; 
 int /*<<< orphan*/  destroy_renderer (struct vo*) ; 
 int /*<<< orphan*/  is_good_renderer (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool try_create_renderer(struct vo *vo, int i, const char *driver,
                                struct mp_rect *rc, int flags)
{
    struct priv *vc = vo->priv;

    // first probe
    SDL_RendererInfo ri;
    if (SDL_GetRenderDriverInfo(i, &ri))
        return false;
    if (!is_good_renderer(&ri, driver, vc->allow_sw, NULL))
        return false;

    bool xy_valid = flags & VO_WIN_FORCE_POS;

    // then actually try
    vc->window = SDL_CreateWindow("MPV",
                                  xy_valid ? rc->x0 : SDL_WINDOWPOS_UNDEFINED,
                                  xy_valid ? rc->y0 : SDL_WINDOWPOS_UNDEFINED,
                                  rc->x1 - rc->x0, rc->y1 - rc->y0,
                                  SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (!vc->window) {
        MP_ERR(vo, "SDL_CreateWindow failed\n");
        destroy_renderer(vo);
        return false;
    }

    vc->renderer = SDL_CreateRenderer(vc->window, i, 0);
    if (!vc->renderer) {
        MP_ERR(vo, "SDL_CreateRenderer failed\n");
        destroy_renderer(vo);
        return false;
    }

    if (SDL_GetRendererInfo(vc->renderer, &vc->renderer_info)) {
        MP_ERR(vo, "SDL_GetRendererInfo failed\n");
        destroy_renderer(vo);
        return false;
    }

    if (!is_good_renderer(&vc->renderer_info, NULL, vc->allow_sw,
                          &vc->osd_format)) {
        MP_ERR(vo, "Renderer '%s' does not fulfill "
                                  "requirements on this system\n",
                                  vc->renderer_info.name);
        destroy_renderer(vo);
        return false;
    }

    if (vc->renderer_index != i) {
        MP_INFO(vo, "Using %s\n", vc->renderer_info.name);
        vc->renderer_index = i;
    }

    if (vc->window_title)
        SDL_SetWindowTitle(vc->window, vc->window_title);

    return true;
}