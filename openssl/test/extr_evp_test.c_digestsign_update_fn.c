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
 int EVP_DigestSignUpdate (void*,unsigned char const*,size_t) ; 

__attribute__((used)) static int digestsign_update_fn(void *ctx, const unsigned char *buf,
                                size_t buflen)
{
    return EVP_DigestSignUpdate(ctx, buf, buflen);
}