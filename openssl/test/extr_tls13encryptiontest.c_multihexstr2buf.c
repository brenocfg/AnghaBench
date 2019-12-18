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
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int OPENSSL_hexchar2int (char const) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static unsigned char *multihexstr2buf(const char *str[3], size_t *len)
{
    size_t outer, inner, curr = 0;
    unsigned char *outbuf;
    size_t totlen = 0;

    /* Check lengths of all input strings are even */
    for (outer = 0; outer < 3; outer++) {
        totlen += strlen(str[outer]);
        if ((totlen & 1) != 0)
            return NULL;
    }

    totlen /= 2;
    outbuf = OPENSSL_malloc(totlen);
    if (outbuf == NULL)
        return NULL;

    for (outer = 0; outer < 3; outer++) {
        for (inner = 0; str[outer][inner] != 0; inner += 2) {
            int hi, lo;

            hi = OPENSSL_hexchar2int(str[outer][inner]);
            lo = OPENSSL_hexchar2int(str[outer][inner + 1]);

            if (hi < 0 || lo < 0) {
                OPENSSL_free(outbuf);
                return NULL;
            }
            outbuf[curr++] = (hi << 4) | lo;
        }
    }

    *len = totlen;
    return outbuf;
}