#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* get_params ) (TYPE_1__*) ;int /*<<< orphan*/ * prov; } ;
struct TYPE_8__ {int* data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  TYPE_2__ EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_flags (TYPE_2__ const*) ; 
 int EVP_CIPH_MODE ; 
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_MODE ; 
 int /*<<< orphan*/  EVP_R_CTRL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_MODE ; 
 TYPE_1__ OSSL_PARAM_END ; 
 TYPE_1__ OSSL_PARAM_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int EVP_CIPHER_mode(const EVP_CIPHER *cipher)
{
    if (cipher->prov != NULL) {
        int mode;

        /* Cipher comes from a provider - so ask the provider for the mode */
        OSSL_PARAM params[] = {
            OSSL_PARAM_int(OSSL_CIPHER_PARAM_MODE, NULL),
            OSSL_PARAM_END
        };

        params[0].data = &mode;

        if (cipher->get_params == NULL) {
            EVPerr(EVP_F_EVP_CIPHER_MODE, EVP_R_CTRL_NOT_IMPLEMENTED);
            return 0;
        }

        if (!cipher->get_params(params))
            return 0;

        return mode;
    }
    return EVP_CIPHER_flags(cipher) & EVP_CIPH_MODE;
}