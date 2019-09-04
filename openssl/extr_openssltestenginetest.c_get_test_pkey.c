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
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  e ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static EVP_PKEY *get_test_pkey(void)
{
    static unsigned char n[] =
        "\x00\xAA\x36\xAB\xCE\x88\xAC\xFD\xFF\x55\x52\x3C\x7F\xC4\x52\x3F"
        "\x90\xEF\xA0\x0D\xF3\x77\x4A\x25\x9F\x2E\x62\xB4\xC5\xD9\x9C\xB5"
        "\xAD\xB3\x00\xA0\x28\x5E\x53\x01\x93\x0E\x0C\x70\xFB\x68\x76\x93"
        "\x9C\xE6\x16\xCE\x62\x4A\x11\xE0\x08\x6D\x34\x1E\xBC\xAC\xA0\xA1"
        "\xF5";
    static unsigned char e[] = "\x11";

    RSA *rsa = RSA_new();
    EVP_PKEY *pk = EVP_PKEY_new();

    if (rsa == NULL || pk == NULL || !EVP_PKEY_assign_RSA(pk, rsa)) {
        RSA_free(rsa);
        EVP_PKEY_free(pk);
        return NULL;
    }

    if (!RSA_set0_key(rsa, BN_bin2bn(n, sizeof(n)-1, NULL),
                      BN_bin2bn(e, sizeof(e)-1, NULL), NULL)) {
        EVP_PKEY_free(pk);
        return NULL;
    }

    return pk;
}