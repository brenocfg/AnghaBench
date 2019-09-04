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
struct vo {TYPE_1__* driver; scalar_t__ eq_opts_cache; scalar_t__ gl_opts_cache; scalar_t__ opts_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* control ) (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_SET_EQUALIZER ; 
 int /*<<< orphan*/  VOCTRL_SET_PANSCAN ; 
 int /*<<< orphan*/  VOCTRL_UPDATE_RENDER_OPTS ; 
 scalar_t__ m_config_cache_update (scalar_t__) ; 
 int /*<<< orphan*/  read_opts (struct vo*) ; 
 int /*<<< orphan*/  stub1 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_opts(void *p)
{
    struct vo *vo = p;

    if (m_config_cache_update(vo->opts_cache)) {
        read_opts(vo);

        // "Legacy" update of video position related options.
        if (vo->driver->control)
            vo->driver->control(vo, VOCTRL_SET_PANSCAN, NULL);
    }

    if (vo->gl_opts_cache && m_config_cache_update(vo->gl_opts_cache)) {
        // "Legacy" update of video GL renderer related options.
        if (vo->driver->control)
            vo->driver->control(vo, VOCTRL_UPDATE_RENDER_OPTS, NULL);
    }

    if (m_config_cache_update(vo->eq_opts_cache)) {
        // "Legacy" update of video equalizer related options.
        if (vo->driver->control)
            vo->driver->control(vo, VOCTRL_SET_EQUALIZER, NULL);
    }
}