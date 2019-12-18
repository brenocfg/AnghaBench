#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int mask_k; int mask_a; scalar_t__ max_ver; scalar_t__ min_ver; } ;
struct TYPE_10__ {TYPE_1__ tmp; } ;
struct TYPE_12__ {TYPE_2__ s3; } ;
struct TYPE_11__ {int algorithm_mkey; int algorithm_auth; int min_tls; scalar_t__ max_tls; int /*<<< orphan*/  strength_bits; int /*<<< orphan*/  max_dtls; int /*<<< orphan*/  min_dtls; } ;
typedef  TYPE_3__ SSL_CIPHER ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 scalar_t__ DTLS_VERSION_GT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DTLS_VERSION_LT (int /*<<< orphan*/ ,scalar_t__) ; 
 int SSL3_VERSION ; 
 scalar_t__ SSL_IS_DTLS (TYPE_4__*) ; 
 int SSL_kECDHE ; 
 int SSL_kECDHEPSK ; 
 int TLS1_VERSION ; 
 int /*<<< orphan*/  ssl_security (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int ssl_cipher_disabled(SSL *s, const SSL_CIPHER *c, int op, int ecdhe)
{
    if (c->algorithm_mkey & s->s3.tmp.mask_k
        || c->algorithm_auth & s->s3.tmp.mask_a)
        return 1;
    if (s->s3.tmp.max_ver == 0)
        return 1;
    if (!SSL_IS_DTLS(s)) {
        int min_tls = c->min_tls;

        /*
         * For historical reasons we will allow ECHDE to be selected by a server
         * in SSLv3 if we are a client
         */
        if (min_tls == TLS1_VERSION && ecdhe
                && (c->algorithm_mkey & (SSL_kECDHE | SSL_kECDHEPSK)) != 0)
            min_tls = SSL3_VERSION;

        if ((min_tls > s->s3.tmp.max_ver) || (c->max_tls < s->s3.tmp.min_ver))
            return 1;
    }
    if (SSL_IS_DTLS(s) && (DTLS_VERSION_GT(c->min_dtls, s->s3.tmp.max_ver)
                           || DTLS_VERSION_LT(c->max_dtls, s->s3.tmp.min_ver)))
        return 1;

    return !ssl_security(s, op, c->strength_bits, 0, (void *)c);
}