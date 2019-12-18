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
struct gl_video {int num_hook_textures; int /*<<< orphan*/  sc; int /*<<< orphan*/ * hook_textures; int /*<<< orphan*/  ra; TYPE_1__* surfaces; int /*<<< orphan*/ * error_diffusion_tex; int /*<<< orphan*/  output_tex; int /*<<< orphan*/  screen_tex; int /*<<< orphan*/  blend_subs_tex; int /*<<< orphan*/  indirect_tex; int /*<<< orphan*/ * integer_tex; int /*<<< orphan*/ * scale_tex; int /*<<< orphan*/ * merge_tex; int /*<<< orphan*/  dither_texture; int /*<<< orphan*/ * scaler; } ;
struct TYPE_2__ {int /*<<< orphan*/  tex; } ;

/* Variables and functions */
 int SCALER_COUNT ; 
 int SURFACES_MAX ; 
 int /*<<< orphan*/  gl_sc_reset_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_video_reset_hooks (struct gl_video*) ; 
 int /*<<< orphan*/  gl_video_reset_surfaces (struct gl_video*) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninit_scaler (struct gl_video*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit_rendering(struct gl_video *p)
{
    for (int n = 0; n < SCALER_COUNT; n++)
        uninit_scaler(p, &p->scaler[n]);

    ra_tex_free(p->ra, &p->dither_texture);

    for (int n = 0; n < 4; n++) {
        ra_tex_free(p->ra, &p->merge_tex[n]);
        ra_tex_free(p->ra, &p->scale_tex[n]);
        ra_tex_free(p->ra, &p->integer_tex[n]);
    }

    ra_tex_free(p->ra, &p->indirect_tex);
    ra_tex_free(p->ra, &p->blend_subs_tex);
    ra_tex_free(p->ra, &p->screen_tex);
    ra_tex_free(p->ra, &p->output_tex);

    for (int n = 0; n < 2; n++)
        ra_tex_free(p->ra, &p->error_diffusion_tex[n]);

    for (int n = 0; n < SURFACES_MAX; n++)
        ra_tex_free(p->ra, &p->surfaces[n].tex);

    for (int n = 0; n < p->num_hook_textures; n++)
        ra_tex_free(p->ra, &p->hook_textures[n]);

    gl_video_reset_surfaces(p);
    gl_video_reset_hooks(p);

    gl_sc_reset_error(p->sc);
}