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
typedef  int /*<<< orphan*/  CTLOG ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int CTLOG_new_from_base64 (int /*<<< orphan*/ **,char*,char const*) ; 
 int /*<<< orphan*/  CT_F_CTLOG_NEW_FROM_CONF ; 
 int /*<<< orphan*/  CT_R_LOG_CONF_MISSING_DESCRIPTION ; 
 int /*<<< orphan*/  CT_R_LOG_CONF_MISSING_KEY ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* NCONF_get_string (int /*<<< orphan*/  const*,char const*,char*) ; 

__attribute__((used)) static int ctlog_new_from_conf(CTLOG **ct_log, const CONF *conf, const char *section)
{
    const char *description = NCONF_get_string(conf, section, "description");
    char *pkey_base64;

    if (description == NULL) {
        CTerr(CT_F_CTLOG_NEW_FROM_CONF, CT_R_LOG_CONF_MISSING_DESCRIPTION);
        return 0;
    }

    pkey_base64 = NCONF_get_string(conf, section, "key");
    if (pkey_base64 == NULL) {
        CTerr(CT_F_CTLOG_NEW_FROM_CONF, CT_R_LOG_CONF_MISSING_KEY);
        return 0;
    }

    return CTLOG_new_from_base64(ct_log, pkey_base64, description);
}