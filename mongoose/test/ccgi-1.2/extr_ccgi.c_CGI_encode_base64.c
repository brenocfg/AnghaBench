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
 char* b64encode ; 
 char* mymalloc (int) ; 

char *
CGI_encode_base64(const void *p, int len) {
    const unsigned char *in = p;
    char *out;
    int save = 0, nbits = 0;
    int i, k = 0;

    if (in == 0 || len <= 0) {
        return 0;
    }
    out = mymalloc(4 + 4 * len / 3);

    /* every three input bytes becomes 4 base64 output characters */

    for (i = 0; i < len; i++) {
        save |= in[i] << (16 - nbits);                 /* 3 x 8 bits in */
        if ((nbits += 8) == 24) {
            out[k++] = b64encode[(save >> 18) & 077]; /* 4 x 6 bits out */
            out[k++] = b64encode[(save >> 12) & 077];
            out[k++] = b64encode[(save >>  6) & 077];
            out[k++] = b64encode[ save        & 077];
            nbits = 0;
            save  = 0;
        }
    }

    /* convert leftover bits */

    if (nbits > 0) {
        for (i = 18; i >= 0; i -= 6) {
            if (nbits > 0) {
                out[k++] = b64encode[(save >> i) & 077];
                nbits -= 6;
            }
            else {
                out[k++] = '=';
            }
        }
    }
    out[k] = 0;
    return out;
}