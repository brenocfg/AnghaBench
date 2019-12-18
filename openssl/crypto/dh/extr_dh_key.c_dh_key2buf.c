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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DH_F_DH_KEY2BUF ; 
 int /*<<< orphan*/  DH_R_BN_ERROR ; 
 int /*<<< orphan*/  DH_R_INVALID_PUBKEY ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 

size_t dh_key2buf(const DH *dh, unsigned char **pbuf_out)
{
    const BIGNUM *pubkey;
    unsigned char *pbuf;
    const BIGNUM *p;
    int p_size;

    DH_get0_pqg(dh, &p, NULL, NULL);
    DH_get0_key(dh, &pubkey, NULL);
    if (p == NULL || pubkey == NULL
            || (p_size = BN_num_bytes(p)) == 0
            || BN_num_bytes(pubkey) == 0) {
        DHerr(DH_F_DH_KEY2BUF, DH_R_INVALID_PUBKEY);
        return 0;
    }
    if ((pbuf = OPENSSL_malloc(p_size)) == NULL) {
        DHerr(DH_F_DH_KEY2BUF, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    /*
     * As per Section 4.2.8.1 of RFC 8446 left pad public
     * key with zeros to the size of p
     */
    if (BN_bn2binpad(pubkey, pbuf, p_size) < 0) {
        OPENSSL_free(pbuf);
        DHerr(DH_F_DH_KEY2BUF, DH_R_BN_ERROR);
        return 0;
    }
    *pbuf_out = pbuf;
    return p_size;
}