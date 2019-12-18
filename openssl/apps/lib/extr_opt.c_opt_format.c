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
 int FORMAT_ASN1 ; 
 int FORMAT_ENGINE ; 
 int FORMAT_HTTP ; 
 int FORMAT_MSBLOB ; 
 int FORMAT_NSS ; 
 int FORMAT_PEM ; 
 int FORMAT_PKCS12 ; 
 int FORMAT_PVK ; 
 int FORMAT_SMIME ; 
 int FORMAT_TEXT ; 
 unsigned long OPT_FMT_ENGINE ; 
 unsigned long OPT_FMT_HTTP ; 
 unsigned long OPT_FMT_MSBLOB ; 
 unsigned long OPT_FMT_NSS ; 
 unsigned long OPT_FMT_PEMDER ; 
 unsigned long OPT_FMT_PKCS12 ; 
 unsigned long OPT_FMT_PVK ; 
 unsigned long OPT_FMT_SMIME ; 
 unsigned long OPT_FMT_TEXT ; 
 int opt_format_error (char const*,unsigned long) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int opt_format(const char *s, unsigned long flags, int *result)
{
    switch (*s) {
    default:
        return 0;
    case 'D':
    case 'd':
        if ((flags & OPT_FMT_PEMDER) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_ASN1;
        break;
    case 'T':
    case 't':
        if ((flags & OPT_FMT_TEXT) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_TEXT;
        break;
    case 'N':
    case 'n':
        if ((flags & OPT_FMT_NSS) == 0)
            return opt_format_error(s, flags);
        if (strcmp(s, "NSS") != 0 && strcmp(s, "nss") != 0)
            return opt_format_error(s, flags);
        *result = FORMAT_NSS;
        break;
    case 'S':
    case 's':
        if ((flags & OPT_FMT_SMIME) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_SMIME;
        break;
    case 'M':
    case 'm':
        if ((flags & OPT_FMT_MSBLOB) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_MSBLOB;
        break;
    case 'E':
    case 'e':
        if ((flags & OPT_FMT_ENGINE) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_ENGINE;
        break;
    case 'H':
    case 'h':
        if ((flags & OPT_FMT_HTTP) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_HTTP;
        break;
    case '1':
        if ((flags & OPT_FMT_PKCS12) == 0)
            return opt_format_error(s, flags);
        *result = FORMAT_PKCS12;
        break;
    case 'P':
    case 'p':
        if (s[1] == '\0' || strcmp(s, "PEM") == 0 || strcmp(s, "pem") == 0) {
            if ((flags & OPT_FMT_PEMDER) == 0)
                return opt_format_error(s, flags);
            *result = FORMAT_PEM;
        } else if (strcmp(s, "PVK") == 0 || strcmp(s, "pvk") == 0) {
            if ((flags & OPT_FMT_PVK) == 0)
                return opt_format_error(s, flags);
            *result = FORMAT_PVK;
        } else if (strcmp(s, "P12") == 0 || strcmp(s, "p12") == 0
                   || strcmp(s, "PKCS12") == 0 || strcmp(s, "pkcs12") == 0) {
            if ((flags & OPT_FMT_PKCS12) == 0)
                return opt_format_error(s, flags);
            *result = FORMAT_PKCS12;
        } else {
            return 0;
        }
        break;
    }
    return 1;
}