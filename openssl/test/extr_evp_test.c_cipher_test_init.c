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
struct TYPE_6__ {int enc; int aead; int /*<<< orphan*/ * fetched_cipher; int /*<<< orphan*/  const* cipher; } ;
struct TYPE_5__ {int skip; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_2__ CIPHER_DATA ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_CIPHER_fetch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/  const*) ; 
 int EVP_CIPHER_mode (int /*<<< orphan*/  const*) ; 
 int EVP_CIPH_CCM_MODE ; 
 int EVP_CIPH_FLAG_AEAD_CIPHER ; 
 int EVP_CIPH_GCM_MODE ; 
 int EVP_CIPH_OCB_MODE ; 
 int EVP_CIPH_SIV_MODE ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (char const*) ; 
 scalar_t__ NID_undef ; 
 scalar_t__ OBJ_ln2nid (char const*) ; 
 scalar_t__ OBJ_sn2nid (char const*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_info (char*,char const*) ; 

__attribute__((used)) static int cipher_test_init(EVP_TEST *t, const char *alg)
{
    const EVP_CIPHER *cipher;
    EVP_CIPHER *fetched_cipher;
    CIPHER_DATA *cdat;
    int m;

    if ((cipher = fetched_cipher = EVP_CIPHER_fetch(NULL, alg, NULL)) == NULL
        && (cipher = EVP_get_cipherbyname(alg)) == NULL) {
        /* If alg has an OID assume disabled algorithm */
        if (OBJ_sn2nid(alg) != NID_undef || OBJ_ln2nid(alg) != NID_undef) {
            t->skip = 1;
            return 1;
        }
        return 0;
    }
    cdat = OPENSSL_zalloc(sizeof(*cdat));
    cdat->cipher = cipher;
    cdat->fetched_cipher = fetched_cipher;
    cdat->enc = -1;
    m = EVP_CIPHER_mode(cipher);
    if (m == EVP_CIPH_GCM_MODE
            || m == EVP_CIPH_OCB_MODE
            || m == EVP_CIPH_SIV_MODE
            || m == EVP_CIPH_CCM_MODE)
        cdat->aead = m;
    else if (EVP_CIPHER_flags(cipher) & EVP_CIPH_FLAG_AEAD_CIPHER)
        cdat->aead = -1;
    else
        cdat->aead = 0;

    t->data = cdat;
    if (fetched_cipher != NULL)
        TEST_info("%s is fetched", alg);
    return 1;
}