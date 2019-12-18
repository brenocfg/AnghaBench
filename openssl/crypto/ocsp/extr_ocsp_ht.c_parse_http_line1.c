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
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char*,...) ; 
 int /*<<< orphan*/  OCSP_F_PARSE_HTTP_LINE1 ; 
 int /*<<< orphan*/  OCSP_R_SERVER_RESPONSE_ERROR ; 
 int /*<<< orphan*/  OCSP_R_SERVER_RESPONSE_PARSE_ERROR ; 
 int /*<<< orphan*/  OCSPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ossl_isspace (char) ; 
 int strlen (char*) ; 
 int strtoul (char*,char**,int) ; 

__attribute__((used)) static int parse_http_line1(char *line)
{
    int retcode;
    char *p, *q, *r;
    /* Skip to first white space (passed protocol info) */

    for (p = line; *p && !ossl_isspace(*p); p++)
        continue;
    if (*p == '\0') {
        OCSPerr(OCSP_F_PARSE_HTTP_LINE1, OCSP_R_SERVER_RESPONSE_PARSE_ERROR);
        return 0;
    }

    /* Skip past white space to start of response code */
    while (*p && ossl_isspace(*p))
        p++;

    if (*p == '\0') {
        OCSPerr(OCSP_F_PARSE_HTTP_LINE1, OCSP_R_SERVER_RESPONSE_PARSE_ERROR);
        return 0;
    }

    /* Find end of response code: first whitespace after start of code */
    for (q = p; *q && !ossl_isspace(*q); q++)
        continue;

    if (*q == '\0') {
        OCSPerr(OCSP_F_PARSE_HTTP_LINE1, OCSP_R_SERVER_RESPONSE_PARSE_ERROR);
        return 0;
    }

    /* Set end of response code and start of message */
    *q++ = 0;

    /* Attempt to parse numeric code */
    retcode = strtoul(p, &r, 10);

    if (*r)
        return 0;

    /* Skip over any leading white space in message */
    while (*q && ossl_isspace(*q))
        q++;

    if (*q) {
        /*
         * Finally zap any trailing white space in message (include CRLF)
         */

        /* We know q has a non white space character so this is OK */
        for (r = q + strlen(q) - 1; ossl_isspace(*r); r--)
            *r = 0;
    }
    if (retcode != 200) {
        OCSPerr(OCSP_F_PARSE_HTTP_LINE1, OCSP_R_SERVER_RESPONSE_ERROR);
        if (*q == '\0')
            ERR_add_error_data(2, "Code=", p);
        else
            ERR_add_error_data(4, "Code=", p, ",Reason=", q);
        return 0;
    }

    return 1;

}