#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* pkey; } ;
typedef  TYPE_2__ X509_PUBKEY ;
struct TYPE_13__ {TYPE_1__* ameth; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* pub_encode ) (TYPE_2__*,TYPE_3__*) ;} ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 int EVP_PKEY_up_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  X509_F_X509_PUBKEY_SET ; 
 int /*<<< orphan*/  X509_PUBKEY_free (TYPE_2__*) ; 
 TYPE_2__* X509_PUBKEY_new () ; 
 int /*<<< orphan*/  X509_R_METHOD_NOT_SUPPORTED ; 
 int /*<<< orphan*/  X509_R_PUBLIC_KEY_ENCODE_ERROR ; 
 int /*<<< orphan*/  X509_R_UNSUPPORTED_ALGORITHM ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__*) ; 

int X509_PUBKEY_set(X509_PUBKEY **x, EVP_PKEY *pkey)
{
    X509_PUBKEY *pk = NULL;

    if (x == NULL)
        return 0;

    if ((pk = X509_PUBKEY_new()) == NULL)
        goto error;

    if (pkey != NULL && pkey->ameth) {
        if (pkey->ameth->pub_encode) {
            if (!pkey->ameth->pub_encode(pk, pkey)) {
                X509err(X509_F_X509_PUBKEY_SET,
                        X509_R_PUBLIC_KEY_ENCODE_ERROR);
                goto error;
            }
        } else {
            X509err(X509_F_X509_PUBKEY_SET, X509_R_METHOD_NOT_SUPPORTED);
            goto error;
        }
    } else {
        X509err(X509_F_X509_PUBKEY_SET, X509_R_UNSUPPORTED_ALGORITHM);
        goto error;
    }

    X509_PUBKEY_free(*x);
    *x = pk;
    pk->pkey = pkey;
    return EVP_PKEY_up_ref(pkey);

 error:
    X509_PUBKEY_free(pk);
    return 0;
}