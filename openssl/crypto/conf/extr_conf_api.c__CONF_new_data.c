#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ CONF ;

/* Variables and functions */
 int /*<<< orphan*/  conf_value_cmp ; 
 int /*<<< orphan*/  conf_value_hash ; 
 int /*<<< orphan*/ * lh_CONF_VALUE_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _CONF_new_data(CONF *conf)
{
    if (conf == NULL) {
        return 0;
    }
    if (conf->data == NULL) {
        conf->data = lh_CONF_VALUE_new(conf_value_hash, conf_value_cmp);
        if (conf->data == NULL)
            return 0;
    }
    return 1;
}