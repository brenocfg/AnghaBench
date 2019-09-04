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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  jsonsl_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSONSL_ERROR_ESCAPE_INVALID ; 
 int /*<<< orphan*/  JSONSL_ERROR_INVALID_CODEPOINT ; 
 int /*<<< orphan*/  JSONSL_ERROR_PERCENT_BADHEX ; 
 int /*<<< orphan*/  JSONSL_ERROR_SUCCESS ; 
 int /*<<< orphan*/  JSONSL_ERROR_UESCAPE_TOOSHORT ; 
 unsigned int JSONSL_SPECIALf_NONASCII ; 
 char get_escape_equiv (unsigned char const) ; 
 int /*<<< orphan*/  is_allowed_escape (unsigned char const) ; 
 int jsonsl__get_uescape_16 (char const*) ; 
 char* jsonsl__writeutf8 (int,char*) ; 

size_t jsonsl_util_unescape_ex(const char *in,
                               char *out,
                               size_t len,
                               const int toEscape[128],
                               unsigned *oflags,
                               jsonsl_error_t *err,
                               const char **errat)
{
    const unsigned char *c = (const unsigned char*)in;
    char *begin_p = out;
    unsigned oflags_s;
    uint16_t last_codepoint = 0;

    if (!oflags) {
        oflags = &oflags_s;
    }
    *oflags = 0;

    #define UNESCAPE_BAIL(e,offset) \
        *err = JSONSL_ERROR_##e; \
        if (errat) { \
            *errat = (const char*)(c+ (ptrdiff_t)(offset)); \
        } \
        return 0;

    for (; len; len--, c++, out++) {
        int uescval;
        if (*c != '\\') {
            /* Not an escape, so we don't care about this */
            goto GT_ASSIGN;
        }

        if (len < 2) {
            UNESCAPE_BAIL(ESCAPE_INVALID, 0);
        }
        if (!is_allowed_escape(c[1])) {
            UNESCAPE_BAIL(ESCAPE_INVALID, 1)
        }
        if ((toEscape && toEscape[(unsigned char)c[1] & 0x7f] == 0 &&
                c[1] != '\\' && c[1] != '"')) {
            /* if we don't want to unescape this string, write the escape sequence to the output */
            *out++ = *c++;
            if (--len == 0)
                break;
            goto GT_ASSIGN;
        }

        if (c[1] != 'u') {
            /* simple skip-and-replace using pre-defined maps.
             * TODO: should the maps actually reflect the desired
             * replacement character in toEscape?
             */
            char esctmp = get_escape_equiv(c[1]);
            if (esctmp) {
                /* Check if there is a corresponding replacement */
                *out = esctmp;
            } else {
                /* Just gobble up the 'reverse-solidus' */
                *out = c[1];
            }
            len--;
            c++;
            /* do not assign, just continue */
            continue;
        }

        /* next == 'u' */
        if (len < 6) {
            /* Need at least six characters.. */
            UNESCAPE_BAIL(UESCAPE_TOOSHORT, 2);
        }

        uescval = jsonsl__get_uescape_16((const char *)c + 2);
        if (uescval == -1) {
            UNESCAPE_BAIL(PERCENT_BADHEX, -1);
        } else if (uescval == 0) {
            UNESCAPE_BAIL(INVALID_CODEPOINT, 2);
        }

        if (last_codepoint) {
            uint16_t w1 = last_codepoint, w2 = (uint16_t)uescval;
            uint32_t cp;

            if (uescval < 0xDC00 || uescval > 0xDFFF) {
                UNESCAPE_BAIL(INVALID_CODEPOINT, -1);
            }

            cp = (w1 & 0x3FF) << 10;
            cp |= (w2 & 0x3FF);
            cp += 0x10000;

            out = jsonsl__writeutf8(cp, out) - 1;
            last_codepoint = 0;

        } else if (uescval < 0xD800 || uescval > 0xDFFF) {
            *oflags |= JSONSL_SPECIALf_NONASCII;
            out = jsonsl__writeutf8(uescval, out) - 1;

        } else if (uescval > 0xD7FF && uescval < 0xDC00) {
            *oflags |= JSONSL_SPECIALf_NONASCII;
            last_codepoint = (uint16_t)uescval;
            out--;
        } else {
            UNESCAPE_BAIL(INVALID_CODEPOINT, 2);
        }

        /* Post uescape cleanup */
        len -= 5; /* Gobble up 5 chars after 'u' */
        c += 5;
        continue;

        /* Only reached by previous branches */
        GT_ASSIGN:
        *out = *c;
    }

    if (last_codepoint) {
        *err = JSONSL_ERROR_INVALID_CODEPOINT;
        return 0;
    }

    *err = JSONSL_ERROR_SUCCESS;
    return out - begin_p;
}