#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_property {int /*<<< orphan*/  name; } ;
struct m_obj_settings {int dummy; } ;
struct m_config_option {scalar_t__ data; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
struct TYPE_5__ {int /*<<< orphan*/  mconfig; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_ERROR ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 129 
#define  M_PROPERTY_SET 128 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 struct m_config_option* m_config_get_co (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_property_generic_option (TYPE_1__*,struct m_property*,int,void*) ; 
 char* print_obj_osd_list (struct m_obj_settings*) ; 
 int /*<<< orphan*/  set_filters (TYPE_1__*,int,struct m_obj_settings*) ; 

__attribute__((used)) static int property_filter(struct m_property *prop, int action, void *arg,
                           MPContext *mpctx, enum stream_type mt)
{
    switch (action) {
    case M_PROPERTY_PRINT: {
        struct m_config_option *opt = m_config_get_co(mpctx->mconfig,
                                                      bstr0(prop->name));
        *(char **)arg = print_obj_osd_list(*(struct m_obj_settings **)opt->data);
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_SET:
        return set_filters(mpctx, mt, *(struct m_obj_settings **)arg) >= 0
            ? M_PROPERTY_OK : M_PROPERTY_ERROR;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}