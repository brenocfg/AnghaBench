#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* algor; } ;
typedef  TYPE_3__ X509_PUBKEY ;
struct TYPE_15__ {TYPE_2__* ameth; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* pub_decode ) (TYPE_4__*,TYPE_3__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_4__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_4__*) ; 
 TYPE_4__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set_type (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_F_X509_PUBKEY_DECODE ; 
 int /*<<< orphan*/  X509_R_METHOD_NOT_SUPPORTED ; 
 int /*<<< orphan*/  X509_R_PUBLIC_KEY_DECODE_ERROR ; 
 int /*<<< orphan*/  X509_R_UNSUPPORTED_ALGORITHM ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int x509_pubkey_decode(EVP_PKEY **ppkey, X509_PUBKEY *key)
{
    EVP_PKEY *pkey = EVP_PKEY_new();

    if (pkey == NULL) {
        X509err(X509_F_X509_PUBKEY_DECODE, ERR_R_MALLOC_FAILURE);
        return -1;
    }

    if (!EVP_PKEY_set_type(pkey, OBJ_obj2nid(key->algor->algorithm))) {
        X509err(X509_F_X509_PUBKEY_DECODE, X509_R_UNSUPPORTED_ALGORITHM);
        goto error;
    }

    if (pkey->ameth->pub_decode) {
        /*
         * Treat any failure of pub_decode as a decode error. In
         * future we could have different return codes for decode
         * errors and fatal errors such as malloc failure.
         */
        if (!pkey->ameth->pub_decode(pkey, key)) {
            X509err(X509_F_X509_PUBKEY_DECODE, X509_R_PUBLIC_KEY_DECODE_ERROR);
            goto error;
        }
    } else {
        X509err(X509_F_X509_PUBKEY_DECODE, X509_R_METHOD_NOT_SUPPORTED);
        goto error;
    }

    *ppkey = pkey;
    return 1;

 error:
    EVP_PKEY_free(pkey);
    return 0;
}