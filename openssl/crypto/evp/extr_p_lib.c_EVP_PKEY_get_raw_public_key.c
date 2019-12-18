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
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_pub_key ) (TYPE_2__ const*,unsigned char*,size_t*) ;} ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_GET_RAW_PUBLIC_KEY ; 
 int /*<<< orphan*/  EVP_R_GET_RAW_KEY_FAILED ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,unsigned char*,size_t*) ; 

int EVP_PKEY_get_raw_public_key(const EVP_PKEY *pkey, unsigned char *pub,
                                size_t *len)
{
     if (pkey->ameth->get_pub_key == NULL) {
        EVPerr(EVP_F_EVP_PKEY_GET_RAW_PUBLIC_KEY,
               EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return 0;
    }

    if (!pkey->ameth->get_pub_key(pkey, pub, len)) {
        EVPerr(EVP_F_EVP_PKEY_GET_RAW_PUBLIC_KEY, EVP_R_GET_RAW_KEY_FAILED);
        return 0;
    }

    return 1;
}