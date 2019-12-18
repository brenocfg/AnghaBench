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
 int /*<<< orphan*/  lh_CONF_VALUE_doall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_CONF_VALUE_doall_LH_CONF_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_CONF_VALUE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_CONF_VALUE_set_down_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_free_hash ; 
 int /*<<< orphan*/  value_free_stack_doall ; 

void _CONF_free_data(CONF *conf)
{
    if (conf == NULL || conf->data == NULL)
        return;

    /* evil thing to make sure the 'OPENSSL_free()' works as expected */
    lh_CONF_VALUE_set_down_load(conf->data, 0);
    lh_CONF_VALUE_doall_LH_CONF_VALUE(conf->data, value_free_hash, conf->data);

    /*
     * We now have only 'section' entries in the hash table. Due to problems
     * with
     */

    lh_CONF_VALUE_doall(conf->data, value_free_stack_doall);
    lh_CONF_VALUE_free(conf->data);
}