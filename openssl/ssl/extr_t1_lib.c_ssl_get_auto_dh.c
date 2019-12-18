#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* cert; TYPE_2__* new_cipher; } ;
struct TYPE_12__ {TYPE_4__ tmp; } ;
struct TYPE_13__ {TYPE_5__ s3; TYPE_1__* cert; } ;
struct TYPE_10__ {int /*<<< orphan*/  privatekey; } ;
struct TYPE_9__ {int algorithm_auth; int strength_bits; } ;
struct TYPE_8__ {int dh_tmp_auto; } ;
typedef  TYPE_6__ SSL ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_get_rfc3526_prime_3072 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_get_rfc3526_prime_8192 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_get_1024_160 () ; 
 int /*<<< orphan*/ * DH_get_2048_224 () ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/  DH_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_security_bits (int /*<<< orphan*/ ) ; 
 int SSL_aNULL ; 
 int SSL_aPSK ; 

DH *ssl_get_auto_dh(SSL *s)
{
    int dh_secbits = 80;
    if (s->cert->dh_tmp_auto == 2)
        return DH_get_1024_160();
    if (s->s3.tmp.new_cipher->algorithm_auth & (SSL_aNULL | SSL_aPSK)) {
        if (s->s3.tmp.new_cipher->strength_bits == 256)
            dh_secbits = 128;
        else
            dh_secbits = 80;
    } else {
        if (s->s3.tmp.cert == NULL)
            return NULL;
        dh_secbits = EVP_PKEY_security_bits(s->s3.tmp.cert->privatekey);
    }

    if (dh_secbits >= 128) {
        DH *dhp = DH_new();
        BIGNUM *p, *g;
        if (dhp == NULL)
            return NULL;
        g = BN_new();
        if (g == NULL || !BN_set_word(g, 2)) {
            DH_free(dhp);
            BN_free(g);
            return NULL;
        }
        if (dh_secbits >= 192)
            p = BN_get_rfc3526_prime_8192(NULL);
        else
            p = BN_get_rfc3526_prime_3072(NULL);
        if (p == NULL || !DH_set0_pqg(dhp, p, NULL, g)) {
            DH_free(dhp);
            BN_free(p);
            BN_free(g);
            return NULL;
        }
        return dhp;
    }
    if (dh_secbits >= 112)
        return DH_get_2048_224();
    return DH_get_1024_160();
}