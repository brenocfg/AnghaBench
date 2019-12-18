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
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_modules_unload (int) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_config_and_unload(CONF *conf)
{
    if (conf != NULL) {
        NCONF_free(conf);
        CONF_modules_unload(1);
    }
}