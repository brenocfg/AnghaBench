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
typedef  int /*<<< orphan*/  seedmask ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_Digest (void*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 scalar_t__ PKCS1_MGF1 (unsigned char*,int,unsigned char*,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  RSA_F_RSA_PADDING_ADD_PKCS1_OAEP_MGF1 ; 
 int /*<<< orphan*/  RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE ; 
 int /*<<< orphan*/  RSA_R_KEY_SIZE_TOO_SMALL ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int RSA_padding_add_PKCS1_OAEP_mgf1(unsigned char *to, int tlen,
                                    const unsigned char *from, int flen,
                                    const unsigned char *param, int plen,
                                    const EVP_MD *md, const EVP_MD *mgf1md)
{
    int rv = 0;
    int i, emlen = tlen - 1;
    unsigned char *db, *seed;
    unsigned char *dbmask = NULL;
    unsigned char seedmask[EVP_MAX_MD_SIZE];
    int mdlen, dbmask_len = 0;

    if (md == NULL)
        md = EVP_sha1();
    if (mgf1md == NULL)
        mgf1md = md;

    mdlen = EVP_MD_size(md);

    /* step 2b: check KLen > nLen - 2 HLen - 2 */
    if (flen > emlen - 2 * mdlen - 1) {
        RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_OAEP_MGF1,
               RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
        return 0;
    }

    if (emlen < 2 * mdlen + 1) {
        RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_OAEP_MGF1,
               RSA_R_KEY_SIZE_TOO_SMALL);
        return 0;
    }

    /* step 3i: EM = 00000000 || maskedMGF || maskedDB */
    to[0] = 0;
    seed = to + 1;
    db = to + mdlen + 1;

    /* step 3a: hash the additional input */
    if (!EVP_Digest((void *)param, plen, db, NULL, md, NULL))
        goto err;
    /* step 3b: zero bytes array of length nLen - KLen - 2 HLen -2 */
    memset(db + mdlen, 0, emlen - flen - 2 * mdlen - 1);
    /* step 3c: DB = HA || PS || 00000001 || K */
    db[emlen - flen - mdlen - 1] = 0x01;
    memcpy(db + emlen - flen - mdlen, from, (unsigned int)flen);
    /* step 3d: generate random byte string */
    if (RAND_bytes(seed, mdlen) <= 0)
        goto err;

    dbmask_len = emlen - mdlen;
    dbmask = OPENSSL_malloc(dbmask_len);
    if (dbmask == NULL) {
        RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_OAEP_MGF1, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* step 3e: dbMask = MGF(mgfSeed, nLen - HLen - 1) */
    if (PKCS1_MGF1(dbmask, dbmask_len, seed, mdlen, mgf1md) < 0)
        goto err;
    /* step 3f: maskedDB = DB XOR dbMask */
    for (i = 0; i < dbmask_len; i++)
        db[i] ^= dbmask[i];

    /* step 3g: mgfSeed = MGF(maskedDB, HLen) */
    if (PKCS1_MGF1(seedmask, mdlen, db, dbmask_len, mgf1md) < 0)
        goto err;
    /* stepo 3h: maskedMGFSeed = mgfSeed XOR mgfSeedMask */
    for (i = 0; i < mdlen; i++)
        seed[i] ^= seedmask[i];
    rv = 1;

 err:
    OPENSSL_cleanse(seedmask, sizeof(seedmask));
    OPENSSL_clear_free(dbmask, dbmask_len);
    return rv;
}