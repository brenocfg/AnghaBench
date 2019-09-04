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
struct gl_video {int output_tex_valid; int /*<<< orphan*/  video_eq; int /*<<< orphan*/  cms; int /*<<< orphan*/  opts_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_lcms_update_options (int /*<<< orphan*/ ) ; 
 scalar_t__ m_config_cache_update (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_csp_equalizer_state_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_from_options (struct gl_video*) ; 

__attribute__((used)) static void gl_video_update_options(struct gl_video *p)
{
    if (m_config_cache_update(p->opts_cache)) {
        gl_lcms_update_options(p->cms);
        reinit_from_options(p);
    }

    if (mp_csp_equalizer_state_changed(p->video_eq))
        p->output_tex_valid = false;
}