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
struct vo {struct priv* priv; } ;
struct priv {scalar_t__ renderer_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/ * SDL_GetHint (int /*<<< orphan*/ ) ; 
 int SDL_GetNumRenderDrivers () ; 
 int /*<<< orphan*/  SDL_HINT_RENDER_DRIVER ; 
 scalar_t__ try_create_renderer (struct vo*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_renderer(struct vo *vo)
{
    struct priv *vc = vo->priv;

    int n = SDL_GetNumRenderDrivers();
    int i;

    if (vc->renderer_index >= 0)
        if (try_create_renderer(vo, vc->renderer_index, NULL))
            return 0;

    for (i = 0; i < n; ++i)
        if (try_create_renderer(vo, i, SDL_GetHint(SDL_HINT_RENDER_DRIVER)))
            return 0;

    for (i = 0; i < n; ++i)
        if (try_create_renderer(vo, i, NULL))
            return 0;

    MP_ERR(vo, "No supported renderer\n");
    return -1;
}