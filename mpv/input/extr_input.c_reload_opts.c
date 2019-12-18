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
struct input_opts {scalar_t__ use_media_keys; scalar_t__ use_appleremote; } ;
struct input_ctx {int using_ar; int using_cocoa_media_keys; struct input_opts* opts; int /*<<< orphan*/  opts_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  cocoa_init_apple_remote () ; 
 int /*<<< orphan*/  cocoa_init_media_keys () ; 
 int /*<<< orphan*/  cocoa_uninit_apple_remote () ; 
 int /*<<< orphan*/  cocoa_uninit_media_keys () ; 
 int /*<<< orphan*/  m_config_cache_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reload_opts(struct input_ctx *ictx, bool shutdown)
{
    m_config_cache_update(ictx->opts_cache);

#if HAVE_COCOA
    struct input_opts *opts = ictx->opts;

    if (ictx->using_ar != (opts->use_appleremote && !shutdown)) {
        ictx->using_ar = !ictx->using_ar;
        if (ictx->using_ar) {
            cocoa_init_apple_remote();
        } else {
            cocoa_uninit_apple_remote();
        }
    }

    if (ictx->using_cocoa_media_keys != (opts->use_media_keys && !shutdown)) {
        ictx->using_cocoa_media_keys = !ictx->using_cocoa_media_keys;
        if (ictx->using_cocoa_media_keys) {
            cocoa_init_media_keys();
        } else {
            cocoa_uninit_media_keys();
        }
    }
#endif
}