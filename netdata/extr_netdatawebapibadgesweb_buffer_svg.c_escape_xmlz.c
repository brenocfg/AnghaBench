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
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static inline size_t escape_xmlz(char *dst, const char *src, size_t len) {
    size_t i = len;

    // required escapes from
    // https://github.com/badges/shields/blob/master/badge.js
    while(*src && i) {
        switch(*src) {
            case '\\':
                *dst++ = '/';
                src++;
                i--;
                break;

            case '&':
                if(i > 5) {
                    strcpy(dst, "&amp;");
                    i -= 5;
                    dst += 5;
                    src++;
                }
                else goto cleanup;
                break;

            case '<':
                if(i > 4) {
                    strcpy(dst, "&lt;");
                    i -= 4;
                    dst += 4;
                    src++;
                }
                else goto cleanup;
                break;

            case '>':
                if(i > 4) {
                    strcpy(dst, "&gt;");
                    i -= 4;
                    dst += 4;
                    src++;
                }
                else goto cleanup;
                break;

            case '"':
                if(i > 6) {
                    strcpy(dst, "&quot;");
                    i -= 6;
                    dst += 6;
                    src++;
                }
                else goto cleanup;
                break;

            case '\'':
                if(i > 6) {
                    strcpy(dst, "&apos;");
                    i -= 6;
                    dst += 6;
                    src++;
                }
                else goto cleanup;
                break;

            default:
                i--;
                *dst++ = *src++;
                break;
        }
    }

cleanup:
    *dst = '\0';
    return len - i;
}