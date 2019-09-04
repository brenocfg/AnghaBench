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
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OCSP_F_OCSP_PARSE_URL ; 
 int /*<<< orphan*/  OCSP_R_ERROR_PARSING_URL ; 
 int /*<<< orphan*/  OCSPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

int OCSP_parse_url(const char *url, char **phost, char **pport, char **ppath,
                   int *pssl)
{
    char *p, *buf;

    char *host, *port;

    *phost = NULL;
    *pport = NULL;
    *ppath = NULL;

    /* dup the buffer since we are going to mess with it */
    buf = OPENSSL_strdup(url);
    if (!buf)
        goto mem_err;

    /* Check for initial colon */
    p = strchr(buf, ':');

    if (!p)
        goto parse_err;

    *(p++) = '\0';

    if (strcmp(buf, "http") == 0) {
        *pssl = 0;
        port = "80";
    } else if (strcmp(buf, "https") == 0) {
        *pssl = 1;
        port = "443";
    } else
        goto parse_err;

    /* Check for double slash */
    if ((p[0] != '/') || (p[1] != '/'))
        goto parse_err;

    p += 2;

    host = p;

    /* Check for trailing part of path */

    p = strchr(p, '/');

    if (!p)
        *ppath = OPENSSL_strdup("/");
    else {
        *ppath = OPENSSL_strdup(p);
        /* Set start of path to 0 so hostname is valid */
        *p = '\0';
    }

    if (!*ppath)
        goto mem_err;

    p = host;
    if (host[0] == '[') {
        /* ipv6 literal */
        host++;
        p = strchr(host, ']');
        if (!p)
            goto parse_err;
        *p = '\0';
        p++;
    }

    /* Look for optional ':' for port number */
    if ((p = strchr(p, ':'))) {
        *p = 0;
        port = p + 1;
    }

    *pport = OPENSSL_strdup(port);
    if (!*pport)
        goto mem_err;

    *phost = OPENSSL_strdup(host);

    if (!*phost)
        goto mem_err;

    OPENSSL_free(buf);

    return 1;

 mem_err:
    OCSPerr(OCSP_F_OCSP_PARSE_URL, ERR_R_MALLOC_FAILURE);
    goto err;

 parse_err:
    OCSPerr(OCSP_F_OCSP_PARSE_URL, OCSP_R_ERROR_PARSING_URL);

 err:
    OPENSSL_free(buf);
    OPENSSL_free(*ppath);
    *ppath = NULL;
    OPENSSL_free(*pport);
    *pport = NULL;
    OPENSSL_free(*phost);
    *phost = NULL;
    return 0;

}