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
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int MP_ICONV_ALLOW_CUTOFF ; 
 int bstr_validate_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*) ; 
 char* mp_uchardet (void*,struct mp_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,...) ; 
 char* ms_bom_guess (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

const char *mp_charset_guess(void *talloc_ctx, struct mp_log *log,  bstr buf,
                             const char *user_cp, int flags)
{
    if (strcasecmp(user_cp, "enca") == 0 || strcasecmp(user_cp, "guess") == 0 ||
        strcasecmp(user_cp, "uchardet") == 0 || strchr(user_cp, ':'))
    {
        mp_err(log, "This syntax for the --sub-codepage option was deprecated "
                    "and has been removed.\n");
        if (strncasecmp(user_cp, "utf8:", 5) == 0) {
            user_cp = user_cp + 5;
        } else {
            user_cp = "";
        }
    }

    if (user_cp[0] == '+') {
        mp_verbose(log, "Forcing charset '%s'.\n", user_cp + 1);
        return user_cp + 1;
    }

    const char *bom_cp = ms_bom_guess(buf);
    if (bom_cp) {
        mp_verbose(log, "Data has a BOM, assuming %s as charset.\n", bom_cp);
        return bom_cp;
    }

    int r = bstr_validate_utf8(buf);
    if (r >= 0 || (r > -8 && (flags & MP_ICONV_ALLOW_CUTOFF))) {
        mp_verbose(log, "Data looks like UTF-8, ignoring user-provided charset.\n");
        return "utf-8";
    }

    const char *res = NULL;
    if (strcasecmp(user_cp, "auto") == 0) {
#if HAVE_UCHARDET
        res = mp_uchardet(talloc_ctx, log, buf);
#endif
        if (!res) {
            mp_verbose(log, "Charset auto-detection failed.\n");
            res = "UTF-8-BROKEN";
        }
    } else {
        res = user_cp;
    }

    mp_verbose(log, "Using charset '%s'.\n", res);
    return res;
}