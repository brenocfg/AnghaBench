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
struct m_obj_settings {int dummy; } ;
struct m_config_option {int /*<<< orphan*/  opt; struct m_obj_settings** data; } ;
struct MPContext {int /*<<< orphan*/  mconfig; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * filter_opt ; 
 struct m_config_option* m_config_get_co (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_copy (int /*<<< orphan*/ ,struct m_obj_settings**,struct m_obj_settings**) ; 
 int /*<<< orphan*/  m_option_free (int /*<<< orphan*/ ,struct m_obj_settings**) ; 
 int /*<<< orphan*/  mp_notify_property (struct MPContext*,int /*<<< orphan*/ ) ; 
 int reinit_filters (struct MPContext*,int) ; 

__attribute__((used)) static int set_filters(struct MPContext *mpctx, enum stream_type mediatype,
                       struct m_obj_settings *new_chain)
{
    bstr option = bstr0(filter_opt[mediatype]);
    struct m_config_option *co = m_config_get_co(mpctx->mconfig, option);
    if (!co)
        return -1;

    struct m_obj_settings **list = co->data;
    struct m_obj_settings *old_settings = *list;
    *list = NULL;
    m_option_copy(co->opt, list, &new_chain);

    bool success = reinit_filters(mpctx, mediatype);

    if (success) {
        m_option_free(co->opt, &old_settings);
        mp_notify_property(mpctx, filter_opt[mediatype]);
    } else {
        m_option_free(co->opt, list);
        *list = old_settings;
        reinit_filters(mpctx, mediatype);
    }

    return success ? 0 : -1;
}