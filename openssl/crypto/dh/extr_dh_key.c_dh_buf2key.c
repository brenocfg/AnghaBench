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
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 size_t BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DH_F_DH_BUF2KEY ; 
 int DH_R_BN_ERROR ; 
 int DH_R_INVALID_PUBKEY ; 
 int DH_R_NO_PARAMETERS_SET ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DH_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int) ; 

int dh_buf2key(DH *dh, const unsigned char *buf, size_t len)
{
    int err_reason = DH_R_BN_ERROR;
    BIGNUM *pubkey = NULL;
    const BIGNUM *p;
    size_t p_size;

    if ((pubkey = BN_bin2bn(buf, len, NULL)) == NULL)
        goto err;
    DH_get0_pqg(dh, &p, NULL, NULL);
    if (p == NULL || (p_size = BN_num_bytes(p)) == 0) {
        err_reason = DH_R_NO_PARAMETERS_SET;
        goto err;
    }
    /*
     * As per Section 4.2.8.1 of RFC 8446 fail if DHE's
     * public key is of size not equal to size of p
     */
    if (BN_is_zero(pubkey) || p_size != len) {
        err_reason = DH_R_INVALID_PUBKEY;
        goto err;
    }
    if (DH_set0_key(dh, pubkey, NULL) != 1)
        goto err;
    return 1;
err:
    DHerr(DH_F_DH_BUF2KEY, err_reason);
    BN_free(pubkey);
    return 0;
}