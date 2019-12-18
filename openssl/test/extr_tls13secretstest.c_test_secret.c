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
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int IVLEN ; 
 int KEYLEN ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  ssl_handshake_hash (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/ * ssl_handshake_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls13_derive_iv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  tls13_derive_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,unsigned char const*,size_t,unsigned char*,size_t,unsigned char*,size_t,int) ; 

__attribute__((used)) static int test_secret(SSL *s, unsigned char *prk,
                       const unsigned char *label, size_t labellen,
                       const unsigned char *ref_secret,
                       const unsigned char *ref_key, const unsigned char *ref_iv)
{
    size_t hashsize;
    unsigned char gensecret[EVP_MAX_MD_SIZE];
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned char key[KEYLEN];
    unsigned char iv[IVLEN];
    const EVP_MD *md = ssl_handshake_md(s);

    if (!ssl_handshake_hash(s, hash, sizeof(hash), &hashsize)) {
        TEST_error("Failed to get hash");
        return 0;
    }

    if (!tls13_hkdf_expand(s, md, prk, label, labellen, hash, hashsize,
                           gensecret, hashsize, 1)) {
        TEST_error("Secret generation failed");
        return 0;
    }

    if (!TEST_mem_eq(gensecret, hashsize, ref_secret, hashsize))
        return 0;

    if (!tls13_derive_key(s, md, gensecret, key, KEYLEN)) {
        TEST_error("Key generation failed");
        return 0;
    }

    if (!TEST_mem_eq(key, KEYLEN, ref_key, KEYLEN))
        return 0;

    if (!tls13_derive_iv(s, md, gensecret, iv, IVLEN)) {
        TEST_error("IV generation failed");
        return 0;
    }

    if (!TEST_mem_eq(iv, IVLEN, ref_iv, IVLEN))
        return 0;

    return 1;
}