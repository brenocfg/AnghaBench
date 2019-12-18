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
typedef  unsigned int uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  convert ;

/* Variables and functions */
 int /*<<< orphan*/  DECIMAL_SIZE (scalar_t__) ; 
 int DP_F_MINUS ; 
 int DP_F_NUM ; 
 int DP_F_PLUS ; 
 int DP_F_SPACE ; 
 int DP_F_UNSIGNED ; 
 int DP_F_UP ; 
 int DP_F_ZERO ; 
 int OSSL_MAX (int,int) ; 
 int /*<<< orphan*/  doapr_outch (char**,char**,size_t*,size_t*,char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
fmtint(char **sbuffer,
       char **buffer,
       size_t *currlen,
       size_t *maxlen, int64_t value, int base, int min, int max, int flags)
{
    int signvalue = 0;
    const char *prefix = "";
    uint64_t uvalue;
    char convert[DECIMAL_SIZE(value) + 3];
    int place = 0;
    int spadlen = 0;
    int zpadlen = 0;
    int caps = 0;

    if (max < 0)
        max = 0;
    uvalue = value;
    if (!(flags & DP_F_UNSIGNED)) {
        if (value < 0) {
            signvalue = '-';
            uvalue = 0 - (uint64_t)value;
        } else if (flags & DP_F_PLUS)
            signvalue = '+';
        else if (flags & DP_F_SPACE)
            signvalue = ' ';
    }
    if (flags & DP_F_NUM) {
        if (base == 8)
            prefix = "0";
        if (base == 16)
            prefix = "0x";
    }
    if (flags & DP_F_UP)
        caps = 1;
    do {
        convert[place++] = (caps ? "0123456789ABCDEF" : "0123456789abcdef")
            [uvalue % (unsigned)base];
        uvalue = (uvalue / (unsigned)base);
    } while (uvalue && (place < (int)sizeof(convert)));
    if (place == sizeof(convert))
        place--;
    convert[place] = 0;

    zpadlen = max - place;
    spadlen =
        min - OSSL_MAX(max, place) - (signvalue ? 1 : 0) - strlen(prefix);
    if (zpadlen < 0)
        zpadlen = 0;
    if (spadlen < 0)
        spadlen = 0;
    if (flags & DP_F_ZERO) {
        zpadlen = OSSL_MAX(zpadlen, spadlen);
        spadlen = 0;
    }
    if (flags & DP_F_MINUS)
        spadlen = -spadlen;

    /* spaces */
    while (spadlen > 0) {
        if (!doapr_outch(sbuffer, buffer, currlen, maxlen, ' '))
            return 0;
        --spadlen;
    }

    /* sign */
    if (signvalue)
        if (!doapr_outch(sbuffer, buffer, currlen, maxlen, signvalue))
            return 0;

    /* prefix */
    while (*prefix) {
        if (!doapr_outch(sbuffer, buffer, currlen, maxlen, *prefix))
            return 0;
        prefix++;
    }

    /* zeros */
    if (zpadlen > 0) {
        while (zpadlen > 0) {
            if (!doapr_outch(sbuffer, buffer, currlen, maxlen, '0'))
                return 0;
            --zpadlen;
        }
    }
    /* digits */
    while (place > 0) {
        if (!doapr_outch(sbuffer, buffer, currlen, maxlen, convert[--place]))
            return 0;
    }

    /* left justified spaces */
    while (spadlen < 0) {
        if (!doapr_outch(sbuffer, buffer, currlen, maxlen, ' '))
            return 0;
        ++spadlen;
    }
    return 1;
}