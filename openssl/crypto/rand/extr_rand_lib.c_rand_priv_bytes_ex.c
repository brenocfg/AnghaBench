#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* bytes ) (unsigned char*,int) ;} ;
typedef  TYPE_1__ RAND_METHOD ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_CTX_get0_private_drbg (int /*<<< orphan*/ *) ; 
 int RAND_DRBG_bytes (int /*<<< orphan*/ *,unsigned char*,int) ; 
 TYPE_1__ const* RAND_OpenSSL () ; 
 TYPE_1__* RAND_get_rand_method () ; 
 int stub1 (unsigned char*,int) ; 

int rand_priv_bytes_ex(OPENSSL_CTX *ctx, unsigned char *buf, int num)
{
    RAND_DRBG *drbg;
    int ret;
    const RAND_METHOD *meth = RAND_get_rand_method();

    if (meth != RAND_OpenSSL())
        return meth->bytes(buf, num);

    drbg = OPENSSL_CTX_get0_private_drbg(ctx);
    if (drbg == NULL)
        return 0;

    ret = RAND_DRBG_bytes(drbg, buf, num);
    return ret;
}