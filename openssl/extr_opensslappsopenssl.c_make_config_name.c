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

/* Variables and functions */
 char* OPENSSL_CONF ; 
 char* OPENSSL_strdup (char const*) ; 
 char* X509_get_default_cert_area () ; 
 char* app_malloc (size_t,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *make_config_name(void)
{
    const char *t;
    size_t len;
    char *p;

    if ((t = getenv("OPENSSL_CONF")) != NULL)
        return OPENSSL_strdup(t);

    t = X509_get_default_cert_area();
    len = strlen(t) + 1 + strlen(OPENSSL_CONF) + 1;
    p = app_malloc(len, "config filename buffer");
    strcpy(p, t);
#ifndef OPENSSL_SYS_VMS
    strcat(p, "/");
#endif
    strcat(p, OPENSSL_CONF);

    return p;
}