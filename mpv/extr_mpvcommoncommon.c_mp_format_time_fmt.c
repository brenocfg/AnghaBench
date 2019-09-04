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
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  appendf (char**,char*,...) ; 
 int lrint (double) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

char *mp_format_time_fmt(const char *fmt, double time)
{
    if (time == MP_NOPTS_VALUE)
        return talloc_strdup(NULL, "unknown");
    char *sign = time < 0 ? "-" : "";
    time = time < 0 ? -time : time;
    long long int itime = time;
    long long int h, m, tm, s;
    int ms = lrint((time - itime) * 1000);
    if (ms >= 1000) {
        ms -= 1000;
        itime += 1;
    }
    s = itime;
    tm = s / 60;
    h = s / 3600;
    s -= h * 3600;
    m = s / 60;
    s -= m * 60;
    char *res = talloc_strdup(NULL, "");
    while (*fmt) {
        if (fmt[0] == '%') {
            fmt++;
            switch (fmt[0]) {
            case 'h': appendf(&res, "%s%lld", sign, h); break;
            case 'H': appendf(&res, "%s%02lld", sign, h); break;
            case 'm': appendf(&res, "%s%lld", sign, tm); break;
            case 'M': appendf(&res, "%02lld", m); break;
            case 's': appendf(&res, "%s%lld", sign, itime); break;
            case 'S': appendf(&res, "%02lld", s); break;
            case 'T': appendf(&res, "%03d", ms); break;
            case 'f': appendf(&res, "%f", time); break;
            case '%': appendf(&res, "%s", "%"); break;
            default: goto error;
            }
            fmt++;
        } else {
            appendf(&res, "%c", *fmt);
            fmt++;
        }
    }
    return res;
error:
    talloc_free(res);
    return NULL;
}