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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ CONF_MODULE ;

/* Variables and functions */
 int sk_CONF_MODULE_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_CONF_MODULE_value (int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  supported_modules ; 

__attribute__((used)) static CONF_MODULE *module_find(const char *name)
{
    CONF_MODULE *tmod;
    int i, nchar;
    char *p;
    p = strrchr(name, '.');

    if (p)
        nchar = p - name;
    else
        nchar = strlen(name);

    for (i = 0; i < sk_CONF_MODULE_num(supported_modules); i++) {
        tmod = sk_CONF_MODULE_value(supported_modules, i);
        if (strncmp(tmod->name, name, nchar) == 0)
            return tmod;
    }

    return NULL;

}