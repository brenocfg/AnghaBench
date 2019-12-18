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
struct TYPE_3__ {int /*<<< orphan*/ * data; void* meth_data; int /*<<< orphan*/ * meth; } ;
typedef  TYPE_1__ CONF ;

/* Variables and functions */
 scalar_t__ CONF_type_default ; 
 int /*<<< orphan*/  default_method ; 

__attribute__((used)) static int def_init_default(CONF *conf)
{
    if (conf == NULL)
        return 0;

    conf->meth = &default_method;
    conf->meth_data = (void *)CONF_type_default;
    conf->data = NULL;

    return 1;
}