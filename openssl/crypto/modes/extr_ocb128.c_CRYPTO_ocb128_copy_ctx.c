#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int max_l_index; int l_index; struct TYPE_7__* l; void* keydec; void* keyenc; } ;
typedef  TYPE_1__ OCB128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_CRYPTO_OCB128_COPY_CTX ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

int CRYPTO_ocb128_copy_ctx(OCB128_CONTEXT *dest, OCB128_CONTEXT *src,
                           void *keyenc, void *keydec)
{
    memcpy(dest, src, sizeof(OCB128_CONTEXT));
    if (keyenc)
        dest->keyenc = keyenc;
    if (keydec)
        dest->keydec = keydec;
    if (src->l) {
        if ((dest->l = OPENSSL_malloc(src->max_l_index * 16)) == NULL) {
            CRYPTOerr(CRYPTO_F_CRYPTO_OCB128_COPY_CTX, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        memcpy(dest->l, src->l, (src->l_index + 1) * 16);
    }
    return 1;
}