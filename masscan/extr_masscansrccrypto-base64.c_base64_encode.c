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

size_t
base64_encode(void *vdst, size_t sizeof_dst, 
              const void *vsrc, size_t sizeof_src)
{
    static const char *b64 =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "+/";
    size_t i = 0;
    size_t d = 0;
    unsigned char *dst = (unsigned char *)vdst;
    const unsigned char *src = (const unsigned char *)vsrc;

    /* encode every 3 bytes of source into 4 bytes of destination text */
    while (i + 3 <= sizeof_src) {
        unsigned n;
        
        /* make sure there is enough space */
        if (d + 4 > sizeof_dst)
            return d;

        /* convert the chars */
        n = src[i]<<16 | src[i+1]<<8 | src[i+2];
        dst[d+0] = b64[ (n>>18) & 0x3F ];
        dst[d+1] = b64[ (n>>12) & 0x3F ];
        dst[d+2] = b64[ (n>> 6) & 0x3F ];
        dst[d+3] = b64[ (n>> 0) & 0x3F ];

        i += 3;
        d += 4;
    }

    /* If the source text isn't an even multiple of 3 characters, then we'll
     * have to append a '=' or '==' to the output to compensate */
    if (i + 2 <= sizeof_src && d + 4 <= sizeof_dst) {
        unsigned n = src[i]<<16 | src[i+1]<<8;
        dst[d+0] = b64[ (n>>18) & 0x3F ];
        dst[d+1] = b64[ (n>>12) & 0x3F ];
        dst[d+2] = b64[ (n>> 6) & 0x3F ];
        dst[d+3] = '=';
        d += 4;
    } else if (i + 1 <= sizeof_src && d + 4 <= sizeof_dst) {
        unsigned n = src[i]<<16 | src[i+1]<<8;
        dst[d+0] = b64[ (n>>18) & 0x3F ];
        dst[d+1] = b64[ (n>>12) & 0x3F ];
        dst[d+2] = '=';
        dst[d+3] = '=';
        d += 4;
    }

    return d;
}