#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ecx_key_op_t ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_5__ {unsigned char* pubkey; unsigned char* privkey; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ ECX_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECX_KEY_OP ; 
 int /*<<< orphan*/  EC_R_INVALID_ENCODING ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ED25519_public_from_private (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  ED448_public_from_private (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
#define  EVP_PKEY_ED25519 131 
#define  EVP_PKEY_ED448 130 
#define  EVP_PKEY_X25519 129 
#define  EVP_PKEY_X448 128 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int KEYLENID (int) ; 
 scalar_t__ KEY_OP_KEYGEN ; 
 scalar_t__ KEY_OP_PUBLIC ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_secure_free (unsigned char*) ; 
 unsigned char* OPENSSL_secure_malloc (int) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 scalar_t__ RAND_priv_bytes (unsigned char*,int) ; 
 int V_ASN1_UNDEF ; 
 int X25519_KEYLEN ; 
 int /*<<< orphan*/  X25519_public_from_private (unsigned char*,unsigned char*) ; 
 int X448_KEYLEN ; 
 int /*<<< orphan*/  X448_public_from_private (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int ecx_key_op(EVP_PKEY *pkey, int id, const X509_ALGOR *palg,
                      const unsigned char *p, int plen, ecx_key_op_t op)
{
    ECX_KEY *key = NULL;
    unsigned char *privkey, *pubkey;

    if (op != KEY_OP_KEYGEN) {
        if (palg != NULL) {
            int ptype;

            /* Algorithm parameters must be absent */
            X509_ALGOR_get0(NULL, &ptype, NULL, palg);
            if (ptype != V_ASN1_UNDEF) {
                ECerr(EC_F_ECX_KEY_OP, EC_R_INVALID_ENCODING);
                return 0;
            }
        }

        if (p == NULL || plen != KEYLENID(id)) {
            ECerr(EC_F_ECX_KEY_OP, EC_R_INVALID_ENCODING);
            return 0;
        }
    }

    key = OPENSSL_zalloc(sizeof(*key));
    if (key == NULL) {
        ECerr(EC_F_ECX_KEY_OP, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    pubkey = key->pubkey;

    if (op == KEY_OP_PUBLIC) {
        memcpy(pubkey, p, plen);
    } else {
        privkey = key->privkey = OPENSSL_secure_malloc(KEYLENID(id));
        if (privkey == NULL) {
            ECerr(EC_F_ECX_KEY_OP, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (op == KEY_OP_KEYGEN) {
            if (RAND_priv_bytes(privkey, KEYLENID(id)) <= 0) {
                OPENSSL_secure_free(privkey);
                key->privkey = NULL;
                goto err;
            }
            if (id == EVP_PKEY_X25519) {
                privkey[0] &= 248;
                privkey[X25519_KEYLEN - 1] &= 127;
                privkey[X25519_KEYLEN - 1] |= 64;
            } else if (id == EVP_PKEY_X448) {
                privkey[0] &= 252;
                privkey[X448_KEYLEN - 1] |= 128;
            }
        } else {
            memcpy(privkey, p, KEYLENID(id));
        }
        switch (id) {
        case EVP_PKEY_X25519:
            X25519_public_from_private(pubkey, privkey);
            break;
        case EVP_PKEY_ED25519:
            ED25519_public_from_private(pubkey, privkey);
            break;
        case EVP_PKEY_X448:
            X448_public_from_private(pubkey, privkey);
            break;
        case EVP_PKEY_ED448:
            /*
             * TODO(3.0): We set the library context to NULL for now. This will
             * need to change.
             */
            ED448_public_from_private(NULL, pubkey, privkey);
            break;
        }
    }

    EVP_PKEY_assign(pkey, id, key);
    return 1;
 err:
    OPENSSL_free(key);
    return 0;
}