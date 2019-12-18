#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* new_cipher; } ;
struct TYPE_9__ {TYPE_2__ tmp; } ;
struct TYPE_11__ {TYPE_4__* cert; TYPE_3__ s3; } ;
struct TYPE_10__ {scalar_t__ psk_identity_hint; } ;
struct TYPE_7__ {unsigned long algorithm_mkey; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 unsigned long SSL_PSK ; 
 unsigned long SSL_kDHE ; 
 unsigned long SSL_kDHEPSK ; 
 unsigned long SSL_kECDHE ; 
 unsigned long SSL_kECDHEPSK ; 
 unsigned long SSL_kPSK ; 
 unsigned long SSL_kRSAPSK ; 
 unsigned long SSL_kSRP ; 

__attribute__((used)) static int send_server_key_exchange(SSL *s)
{
    unsigned long alg_k = s->s3.tmp.new_cipher->algorithm_mkey;

    /*
     * only send a ServerKeyExchange if DH or fortezza but we have a
     * sign only certificate PSK: may send PSK identity hints For
     * ECC ciphersuites, we send a serverKeyExchange message only if
     * the cipher suite is either ECDH-anon or ECDHE. In other cases,
     * the server certificate contains the server's public key for
     * key exchange.
     */
    if (alg_k & (SSL_kDHE | SSL_kECDHE)
        /*
         * PSK: send ServerKeyExchange if PSK identity hint if
         * provided
         */
#ifndef OPENSSL_NO_PSK
        /* Only send SKE if we have identity hint for plain PSK */
        || ((alg_k & (SSL_kPSK | SSL_kRSAPSK))
            && s->cert->psk_identity_hint)
        /* For other PSK always send SKE */
        || (alg_k & (SSL_PSK & (SSL_kDHEPSK | SSL_kECDHEPSK)))
#endif
#ifndef OPENSSL_NO_SRP
        /* SRP: send ServerKeyExchange */
        || (alg_k & SSL_kSRP)
#endif
        ) {
        return 1;
    }

    return 0;
}