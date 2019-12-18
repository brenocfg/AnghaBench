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
 long INT_MAX ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 

int EVP_hex2ctrl(int (*cb)(void *ctx, int cmd, void *buf, size_t buflen),
                 void *ctx, int cmd, const char *hex)
{
    unsigned char *bin;
    long binlen;
    int rv = -1;

    bin = OPENSSL_hexstr2buf(hex, &binlen);
    if (bin == NULL)
        return 0;
    if (binlen <= INT_MAX)
        rv = cb(ctx, cmd, bin, binlen);
    OPENSSL_free(bin);
    return rv;
}