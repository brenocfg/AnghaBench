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
struct bstr {scalar_t__ len; unsigned int* start; } ;

/* Variables and functions */
 int bstr_parse_utf8_code_length (unsigned int) ; 

int bstr_decode_utf8(struct bstr s, struct bstr *out_next)
{
    if (s.len == 0)
        return -1;
    unsigned int codepoint = s.start[0];
    s.start++; s.len--;
    if (codepoint >= 128) {
        int bytes = bstr_parse_utf8_code_length(codepoint);
        if (bytes < 1 || s.len < bytes - 1)
            return -1;
        codepoint &= 127 >> bytes;
        for (int n = 1; n < bytes; n++) {
            int tmp = (unsigned char)s.start[0];
            if ((tmp & 0xC0) != 0x80)
                return -1;
            codepoint = (codepoint << 6) | (tmp & ~0xC0);
            s.start++; s.len--;
        }
        if (codepoint > 0x10FFFF || (codepoint >= 0xD800 && codepoint <= 0xDFFF))
            return -1;
        // Overlong sequences - check taken from libavcodec.
        // (The only reason we even bother with this is to make libavcodec's
        //  retarded subtitle utf-8 check happy.)
        unsigned int min = bytes == 2 ? 0x80 : 1 << (5 * bytes - 4);
        if (codepoint < min)
            return -1;
    }
    if (out_next)
        *out_next = s;
    return codepoint;
}