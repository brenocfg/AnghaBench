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
struct priv {int renderer_index; TYPE_1__ renderer_info; int /*<<< orphan*/  osd_format; int /*<<< orphan*/  allow_sw; int /*<<< orphan*/  renderer; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ SDL_RendererInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,...) ; 
 int /*<<< orphan*/  MP_INFO (struct vo*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateRenderer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_GetRenderDriverInfo (int,TYPE_1__*) ; 
 scalar_t__ SDL_GetRendererInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_renderer (struct vo*) ; 
 int /*<<< orphan*/  is_good_renderer (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool try_create_renderer(struct vo *vo, int i, const char *driver)
{
    struct priv *vc = vo->priv;

    // first probe
    SDL_RendererInfo ri;
    if (SDL_GetRenderDriverInfo(i, &ri))
        return false;
    if (!is_good_renderer(&ri, driver, vc->allow_sw, NULL))
        return false;

    vc->renderer = SDL_CreateRenderer(vc->window, i, 0);
    if (!vc->renderer) {
        MP_ERR(vo, "SDL_CreateRenderer failed\n");
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

    return true;
}