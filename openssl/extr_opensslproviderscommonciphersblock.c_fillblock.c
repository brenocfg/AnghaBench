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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

size_t fillblock(unsigned char *buf, size_t *buflen, size_t blocksize,
                 const unsigned char **in, size_t *inlen)
{
    size_t blockmask = ~(blocksize - 1);

    assert(*buflen <= blocksize);
    assert(blocksize > 0 && (blocksize & (blocksize - 1)) == 0);

    if (*buflen != blocksize && (*buflen != 0 || *inlen < blocksize)) {
        size_t bufremain = blocksize - *buflen;

        if (*inlen < bufremain)
            bufremain = *inlen;
        memcpy(buf + *buflen, *in, bufremain);
        *in += bufremain;
        *inlen -= bufremain;
        *buflen += bufremain;
    }

    return *inlen & blockmask;
}