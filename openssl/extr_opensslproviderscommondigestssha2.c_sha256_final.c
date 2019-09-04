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
 size_t SHA256_DIGEST_LENGTH ; 
 scalar_t__ SHA256_Final (unsigned char*,void*) ; 

__attribute__((used)) static int sha256_final(void *ctx,
                        unsigned char *md, size_t *mdl, size_t mdsz)
{
    if (mdsz >= SHA256_DIGEST_LENGTH
        && SHA256_Final(md, ctx)) {
        *mdl = SHA256_DIGEST_LENGTH;
        return 1;
    }

    return 0;
}