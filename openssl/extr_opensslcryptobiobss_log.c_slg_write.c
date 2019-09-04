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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_SLG_WRITE ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
#define  LOG_ALERT 135 
#define  LOG_CRIT 134 
#define  LOG_DEBUG 133 
#define  LOG_EMERG 132 
#define  LOG_ERR 131 
#define  LOG_INFO 130 
#define  LOG_NOTICE 129 
#define  LOG_WARNING 128 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  xsyslog (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int slg_write(BIO *b, const char *in, int inl)
{
    int ret = inl;
    char *buf;
    char *pp;
    int priority, i;
    static const struct {
        int strl;
        char str[10];
        int log_level;
    } mapping[] = {
        {
            6, "PANIC ", LOG_EMERG
        },
        {
            6, "EMERG ", LOG_EMERG
        },
        {
            4, "EMR ", LOG_EMERG
        },
        {
            6, "ALERT ", LOG_ALERT
        },
        {
            4, "ALR ", LOG_ALERT
        },
        {
            5, "CRIT ", LOG_CRIT
        },
        {
            4, "CRI ", LOG_CRIT
        },
        {
            6, "ERROR ", LOG_ERR
        },
        {
            4, "ERR ", LOG_ERR
        },
        {
            8, "WARNING ", LOG_WARNING
        },
        {
            5, "WARN ", LOG_WARNING
        },
        {
            4, "WAR ", LOG_WARNING
        },
        {
            7, "NOTICE ", LOG_NOTICE
        },
        {
            5, "NOTE ", LOG_NOTICE
        },
        {
            4, "NOT ", LOG_NOTICE
        },
        {
            5, "INFO ", LOG_INFO
        },
        {
            4, "INF ", LOG_INFO
        },
        {
            6, "DEBUG ", LOG_DEBUG
        },
        {
            4, "DBG ", LOG_DEBUG
        },
        {
            0, "", LOG_ERR
        }
        /* The default */
    };

    if ((buf = OPENSSL_malloc(inl + 1)) == NULL) {
        BIOerr(BIO_F_SLG_WRITE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    memcpy(buf, in, inl);
    buf[inl] = '\0';

    i = 0;
    while (strncmp(buf, mapping[i].str, mapping[i].strl) != 0)
        i++;
    priority = mapping[i].log_level;
    pp = buf + mapping[i].strl;

    xsyslog(b, priority, pp);

    OPENSSL_free(buf);
    return ret;
}