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
typedef  int OSSL_CMP_severity ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,int) ; 
 int OSSL_CMP_LOG_ALERT ; 
 int OSSL_CMP_LOG_CRIT ; 
 int OSSL_CMP_LOG_DEBUG ; 
 int OSSL_CMP_LOG_EMERG ; 
 int OSSL_CMP_LOG_ERR ; 
 int OSSL_CMP_LOG_INFO ; 
 int OSSL_CMP_LOG_NOTICE ; 
 int /*<<< orphan*/  OSSL_CMP_LOG_PREFIX ; 
 int OSSL_CMP_LOG_WARNING ; 
 int max_level_len ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSSL_CMP_severity parse_level(const char *level)
{
    const char *end_level = strchr(level, ':');
    int len;
    char level_copy[max_level_len + 1];

    if (end_level == NULL)
        return -1;

    if (strncmp(level, OSSL_CMP_LOG_PREFIX,
                strlen(OSSL_CMP_LOG_PREFIX)) == 0)
        level += strlen(OSSL_CMP_LOG_PREFIX);
    len = end_level - level;
    if (len > max_level_len)
        return -1;
    OPENSSL_strlcpy(level_copy, level, len + 1);
    return
        strcmp(level_copy, "EMERG") == 0 ? OSSL_CMP_LOG_EMERG :
        strcmp(level_copy, "ALERT") == 0 ? OSSL_CMP_LOG_ALERT :
        strcmp(level_copy, "CRIT") == 0 ? OSSL_CMP_LOG_CRIT :
        strcmp(level_copy, "ERROR") == 0 ? OSSL_CMP_LOG_ERR :
        strcmp(level_copy, "WARN") == 0 ? OSSL_CMP_LOG_WARNING :
        strcmp(level_copy, "NOTE") == 0 ? OSSL_CMP_LOG_NOTICE :
        strcmp(level_copy, "INFO") == 0 ? OSSL_CMP_LOG_INFO :
        strcmp(level_copy, "DEBUG") == 0 ? OSSL_CMP_LOG_DEBUG :
        -1;
}