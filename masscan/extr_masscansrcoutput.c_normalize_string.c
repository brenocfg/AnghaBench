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
 scalar_t__ isprint (unsigned char) ; 

const char *
normalize_string(const unsigned char *px, size_t length,
                 char *buf, size_t buf_len)
{
    size_t i=0;
    size_t offset = 0;


    for (i=0; i<length; i++) {
        unsigned char c = px[i];

        if (isprint(c) && c != '<' && c != '>' && c != '&' && c != '\\' && c != '\"' && c != '\'') {
            if (offset + 2 < buf_len)
                buf[offset++] = px[i];
        } else {
            if (offset + 5 < buf_len) {
                buf[offset++] = '\\';
                buf[offset++] = 'x';
                buf[offset++] = "0123456789abcdef"[px[i]>>4];
                buf[offset++] = "0123456789abcdef"[px[i]&0xF];
            }
        }
    }

    buf[offset] = '\0';

    return buf;
}