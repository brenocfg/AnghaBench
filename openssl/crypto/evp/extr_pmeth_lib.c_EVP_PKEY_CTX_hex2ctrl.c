#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pmeth; } ;
struct TYPE_5__ {int (* ctrl ) (TYPE_2__*,int,long,unsigned char*) ;} ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 long INT_MAX ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 
 int stub1 (TYPE_2__*,int,long,unsigned char*) ; 

int EVP_PKEY_CTX_hex2ctrl(EVP_PKEY_CTX *ctx, int cmd, const char *hex)
{
    unsigned char *bin;
    long binlen;
    int rv = -1;

    bin = OPENSSL_hexstr2buf(hex, &binlen);
    if (bin == NULL)
        return 0;
    if (binlen <= INT_MAX)
        rv = ctx->pmeth->ctrl(ctx, cmd, binlen, bin);
    OPENSSL_free(bin);
    return rv;
}