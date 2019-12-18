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
 int /*<<< orphan*/  CONF_F_NCONF_GET_STRING ; 
 int /*<<< orphan*/  CONF_R_NO_CONF_OR_ENVIRONMENT_VARIABLE ; 
 int /*<<< orphan*/  CONF_R_NO_VALUE ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*,char*,char const*) ; 
 char* _CONF_get_string (int /*<<< orphan*/  const*,char const*,char const*) ; 

char *NCONF_get_string(const CONF *conf, const char *group, const char *name)
{
    char *s = _CONF_get_string(conf, group, name);

    /*
     * Since we may get a value from an environment variable even if conf is
     * NULL, let's check the value first
     */
    if (s)
        return s;

    if (conf == NULL) {
        CONFerr(CONF_F_NCONF_GET_STRING,
                CONF_R_NO_CONF_OR_ENVIRONMENT_VARIABLE);
        return NULL;
    }
    CONFerr(CONF_F_NCONF_GET_STRING, CONF_R_NO_VALUE);
    ERR_add_error_data(4, "group=", group, " name=", name);
    return NULL;
}