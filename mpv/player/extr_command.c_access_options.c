#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m_property_action_arg {int action; scalar_t__ arg; int /*<<< orphan*/  key; } ;
struct m_option {int dummy; } ;
struct m_config_option {struct m_option* opt; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  mconfig; int /*<<< orphan*/  playing; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_ERROR ; 
#define  M_PROPERTY_GET 130 
#define  M_PROPERTY_GET_TYPE 129 
 int M_PROPERTY_NOT_IMPLEMENTED ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_SET 128 
 int M_PROPERTY_UNAVAILABLE ; 
 int M_PROPERTY_UNKNOWN ; 
 int M_SETOPT_BACKUP ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 struct m_config_option* m_config_get_co (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int m_config_set_option_raw (int /*<<< orphan*/ ,struct m_config_option*,scalar_t__,int) ; 
 int /*<<< orphan*/  m_option_copy (struct m_option*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_1__*) ; 

__attribute__((used)) static int access_options(struct m_property_action_arg *ka, bool local,
                          MPContext *mpctx)
{
    struct m_config_option *opt = m_config_get_co(mpctx->mconfig,
                                                  bstr0(ka->key));
    if (!opt)
        return M_PROPERTY_UNKNOWN;
    if (!opt->data)
        return M_PROPERTY_UNAVAILABLE;

    switch (ka->action) {
    case M_PROPERTY_GET:
        m_option_copy(opt->opt, ka->arg, opt->data);
        return M_PROPERTY_OK;
    case M_PROPERTY_SET: {
        if (local && !mpctx->playing)
            return M_PROPERTY_ERROR;
        int flags = local ? M_SETOPT_BACKUP : 0;
        int r = m_config_set_option_raw(mpctx->mconfig, opt, ka->arg, flags);
        mp_wakeup_core(mpctx);
        return r < 0 ? M_PROPERTY_ERROR : M_PROPERTY_OK;
    }
    case M_PROPERTY_GET_TYPE:
        *(struct m_option *)ka->arg = *opt->opt;
        return M_PROPERTY_OK;
    }
    return M_PROPERTY_NOT_IMPLEMENTED;
}