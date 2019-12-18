#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {char* section; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ CONF_VALUE ;
typedef  TYPE_2__ CONF ;

/* Variables and functions */
 TYPE_1__* lh_CONF_VALUE_retrieve (int /*<<< orphan*/ ,TYPE_1__*) ; 

CONF_VALUE *_CONF_get_section(const CONF *conf, const char *section)
{
    CONF_VALUE *v, vv;

    if ((conf == NULL) || (section == NULL))
        return NULL;
    vv.name = NULL;
    vv.section = (char *)section;
    v = lh_CONF_VALUE_retrieve(conf->data, &vv);
    return v;
}