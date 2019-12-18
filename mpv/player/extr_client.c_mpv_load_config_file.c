#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* mpctx; } ;
typedef  TYPE_2__ mpv_handle ;
struct TYPE_6__ {int /*<<< orphan*/  mconfig; } ;

/* Variables and functions */
 int MPV_ERROR_INVALID_PARAMETER ; 
 int MPV_ERROR_OPTION_ERROR ; 
 int /*<<< orphan*/  lock_core (TYPE_2__*) ; 
 int m_config_parse_config_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_core (TYPE_2__*) ; 

int mpv_load_config_file(mpv_handle *ctx, const char *filename)
{
    lock_core(ctx);
    int r = m_config_parse_config_file(ctx->mpctx->mconfig, filename, NULL, 0);
    unlock_core(ctx);
    if (r == 0)
        return MPV_ERROR_INVALID_PARAMETER;
    if (r < 0)
        return MPV_ERROR_OPTION_ERROR;
    return 0;
}