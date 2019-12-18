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
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

int trailingdata(unsigned char *buf, size_t *buflen, size_t blocksize,
                 const unsigned char **in, size_t *inlen)
{
    if (*inlen == 0)
        return 1;

    if (*buflen + *inlen > blocksize) {
        ERR_raise(ERR_LIB_PROV, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    memcpy(buf + *buflen, *in, *inlen);
    *buflen += *inlen;
    *inlen = 0;

    return 1;
}