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
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_CONF ; 
 char* OPENSSL_malloc (int) ; 
 char* OPENSSL_strdup (char*) ; 
 int /*<<< orphan*/  X509_get_default_cert_area () ; 
 char* ossl_safe_getenv (char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

char *CONF_get1_default_config_file(void)
{
    char *file, *sep = "";
    int len;

    if ((file = ossl_safe_getenv("OPENSSL_CONF")) != NULL)
        return OPENSSL_strdup(file);

    len = strlen(X509_get_default_cert_area());
#ifndef OPENSSL_SYS_VMS
    len++;
    sep = "/";
#endif
    len += strlen(OPENSSL_CONF);

    file = OPENSSL_malloc(len + 1);

    if (file == NULL)
        return NULL;
    BIO_snprintf(file, len + 1, "%s%s%s", X509_get_default_cert_area(),
                 sep, OPENSSL_CONF);

    return file;
}