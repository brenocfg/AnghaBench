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
typedef  enum BIO_hostserv_priorities { ____Placeholder_BIO_hostserv_priorities } BIO_hostserv_priorities ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_BIO_PARSE_HOSTSERV ; 
 int BIO_PARSE_PRIO_HOST ; 
 int /*<<< orphan*/  BIO_R_AMBIGUOUS_HOST_OR_SERVICE ; 
 int /*<<< orphan*/  BIO_R_MALFORMED_HOST_OR_SERVICE ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char* OPENSSL_strndup (char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

int BIO_parse_hostserv(const char *hostserv, char **host, char **service,
                       enum BIO_hostserv_priorities hostserv_prio)
{
    const char *h = NULL; size_t hl = 0;
    const char *p = NULL; size_t pl = 0;

    if (*hostserv == '[') {
        if ((p = strchr(hostserv, ']')) == NULL)
            goto spec_err;
        h = hostserv + 1;
        hl = p - h;
        p++;
        if (*p == '\0')
            p = NULL;
        else if (*p != ':')
            goto spec_err;
        else {
            p++;
            pl = strlen(p);
        }
    } else {
        const char *p2 = strrchr(hostserv, ':');
        p = strchr(hostserv, ':');

        /*-
         * Check for more than one colon.  There are three possible
         * interpretations:
         * 1. IPv6 address with port number, last colon being separator.
         * 2. IPv6 address only.
         * 3. IPv6 address only if hostserv_prio == BIO_PARSE_PRIO_HOST,
         *    IPv6 address and port number if hostserv_prio == BIO_PARSE_PRIO_SERV
         * Because of this ambiguity, we currently choose to make it an
         * error.
         */
        if (p != p2)
            goto amb_err;

        if (p != NULL) {
            h = hostserv;
            hl = p - h;
            p++;
            pl = strlen(p);
        } else if (hostserv_prio == BIO_PARSE_PRIO_HOST) {
            h = hostserv;
            hl = strlen(h);
        } else {
            p = hostserv;
            pl = strlen(p);
        }
    }

    if (p != NULL && strchr(p, ':'))
        goto spec_err;

    if (h != NULL && host != NULL) {
        if (hl == 0
            || (hl == 1 && h[0] == '*')) {
            *host = NULL;
        } else {
            *host = OPENSSL_strndup(h, hl);
            if (*host == NULL)
                goto memerr;
        }
    }
    if (p != NULL && service != NULL) {
        if (pl == 0
            || (pl == 1 && p[0] == '*')) {
            *service = NULL;
        } else {
            *service = OPENSSL_strndup(p, pl);
            if (*service == NULL)
                goto memerr;
        }
    }

    return 1;
 amb_err:
    BIOerr(BIO_F_BIO_PARSE_HOSTSERV, BIO_R_AMBIGUOUS_HOST_OR_SERVICE);
    return 0;
 spec_err:
    BIOerr(BIO_F_BIO_PARSE_HOSTSERV, BIO_R_MALFORMED_HOST_OR_SERVICE);
    return 0;
 memerr:
    BIOerr(BIO_F_BIO_PARSE_HOSTSERV, ERR_R_MALLOC_FAILURE);
    return 0;
}