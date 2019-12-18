#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mpv_node {int /*<<< orphan*/  u; scalar_t__ format; } ;
struct m_option {TYPE_2__* type; } ;
struct TYPE_9__ {TYPE_1__* mpctx; } ;
typedef  TYPE_3__ mpv_handle ;
typedef  scalar_t__ mpv_format ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  mconfig; } ;

/* Variables and functions */
 int MPV_ERROR_OPTION_ERROR ; 
 int MPV_ERROR_OPTION_FORMAT ; 
 int MPV_ERROR_OPTION_NOT_FOUND ; 
 scalar_t__ MPV_FORMAT_NODE ; 
#define  M_OPT_INVALID 131 
#define  M_OPT_MISSING_PARAM 130 
#define  M_OPT_OUT_OF_RANGE 129 
#define  M_OPT_UNKNOWN 128 
 int /*<<< orphan*/  bstr0 (char const*) ; 
 struct m_option* get_mp_type (scalar_t__) ; 
 int /*<<< orphan*/  lock_core (TYPE_3__*) ; 
 int m_config_set_option_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_core (TYPE_3__*) ; 

int mpv_set_option(mpv_handle *ctx, const char *name, mpv_format format,
                   void *data)
{
    const struct m_option *type = get_mp_type(format);
    if (!type)
        return MPV_ERROR_OPTION_FORMAT;
    struct mpv_node tmp;
    if (format != MPV_FORMAT_NODE) {
        tmp.format = format;
        memcpy(&tmp.u, data, type->type->size);
        data = &tmp;
    }
    lock_core(ctx);
    int err = m_config_set_option_node(ctx->mpctx->mconfig, bstr0(name), data, 0);
    unlock_core(ctx);
    switch (err) {
    case M_OPT_MISSING_PARAM:
    case M_OPT_INVALID:
        return MPV_ERROR_OPTION_ERROR;
    case M_OPT_OUT_OF_RANGE:
        return MPV_ERROR_OPTION_FORMAT;
    case M_OPT_UNKNOWN:
        return MPV_ERROR_OPTION_NOT_FOUND;
    default:
        if (err >= 0)
            return 0;
        return MPV_ERROR_OPTION_ERROR;
    }
}