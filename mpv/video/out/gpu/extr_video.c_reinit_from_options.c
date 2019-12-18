#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gl_video_opts {scalar_t__ interpolation; int /*<<< orphan*/  pbo; int /*<<< orphan*/  shader_cache_dir; int /*<<< orphan*/  background; } ;
struct gl_video {int dsi_warned; struct gl_video_opts opts; int /*<<< orphan*/  global; TYPE_2__* ra; int /*<<< orphan*/  sc; int /*<<< orphan*/  clear_color; int /*<<< orphan*/  force_clear_color; TYPE_1__* opts_cache; int /*<<< orphan*/  cms; int /*<<< orphan*/  use_lut_3d; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_pbo; } ;
struct TYPE_3__ {scalar_t__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct gl_video*,char*) ; 
 int /*<<< orphan*/  check_gl_features (struct gl_video*) ; 
 int /*<<< orphan*/  gl_lcms_has_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_sc_set_cache_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_video_setup_hooks (struct gl_video*) ; 
 int /*<<< orphan*/  m_option_type_choice ; 
 int /*<<< orphan*/  mp_read_option_raw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  reinit_osd (struct gl_video*) ; 
 int /*<<< orphan*/  uninit_rendering (struct gl_video*) ; 

__attribute__((used)) static void reinit_from_options(struct gl_video *p)
{
    p->use_lut_3d = gl_lcms_has_profile(p->cms);

    // Copy the option fields, so that check_gl_features() can mutate them.
    // This works only for the fields themselves of course, not for any memory
    // referenced by them.
    p->opts = *(struct gl_video_opts *)p->opts_cache->opts;

    if (!p->force_clear_color)
        p->clear_color = p->opts.background;

    check_gl_features(p);
    uninit_rendering(p);
    gl_sc_set_cache_dir(p->sc, p->opts.shader_cache_dir);
    p->ra->use_pbo = p->opts.pbo;
    gl_video_setup_hooks(p);
    reinit_osd(p);

    int vs;
    mp_read_option_raw(p->global, "video-sync", &m_option_type_choice, &vs);
    if (p->opts.interpolation && !vs && !p->dsi_warned) {
        MP_WARN(p, "Interpolation now requires enabling display-sync mode.\n"
                   "E.g.: --video-sync=display-resample\n");
        p->dsi_warned = true;
    }
}