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
typedef  int /*<<< orphan*/  ocb128_f ;
typedef  int /*<<< orphan*/  block128_f ;
typedef  int /*<<< orphan*/  OCB128_CONTEXT ;

/* Variables and functions */
 int CRYPTO_ocb128_init (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 

OCB128_CONTEXT *CRYPTO_ocb128_new(void *keyenc, void *keydec,
                                  block128_f encrypt, block128_f decrypt,
                                  ocb128_f stream)
{
    OCB128_CONTEXT *octx;
    int ret;

    if ((octx = OPENSSL_malloc(sizeof(*octx))) != NULL) {
        ret = CRYPTO_ocb128_init(octx, keyenc, keydec, encrypt, decrypt,
                                 stream);
        if (ret)
            return octx;
        OPENSSL_free(octx);
    }

    return NULL;
}