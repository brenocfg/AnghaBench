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
struct priv {int /*<<< orphan*/  renderer; struct osd_bitmap_surface* osd_surfaces; } ;
struct osd_target {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; scalar_t__ tex2; scalar_t__ tex; } ;
struct osd_bitmap_surface {int num_targets; struct osd_target* targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderCopy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void draw_osd_part(struct vo *vo, int index)
{
    struct priv *vc = vo->priv;
    struct osd_bitmap_surface *sfc = &vc->osd_surfaces[index];
    int i;

    for (i = 0; i < sfc->num_targets; i++) {
        struct osd_target *target = sfc->targets + i;
        if (target->tex)
            SDL_RenderCopy(vc->renderer, target->tex,
                           &target->source, &target->dest);
        if (target->tex2)
            SDL_RenderCopy(vc->renderer, target->tex2,
                           &target->source, &target->dest);
    }
}