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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int psk_key2bn(const char *pskkey, unsigned char *psk,
                      unsigned int max_psk_len)
{
    int ret;
    BIGNUM *bn = NULL;

    ret = BN_hex2bn(&bn, pskkey);
    if (!ret) {
        BIO_printf(bio_err, "Could not convert PSK key '%s' to BIGNUM\n",
                   pskkey);
        BN_free(bn);
        return 0;
    }
    if (BN_num_bytes(bn) > (int)max_psk_len) {
        BIO_printf(bio_err,
                   "psk buffer of callback is too small (%d) for key (%d)\n",
                   max_psk_len, BN_num_bytes(bn));
        BN_free(bn);
        return 0;
    }
    ret = BN_bn2bin(bn, psk);
    BN_free(bn);
    return ret;
}