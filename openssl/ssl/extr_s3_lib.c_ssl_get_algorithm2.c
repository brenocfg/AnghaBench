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
struct TYPE_9__ {TYPE_1__* new_cipher; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
struct TYPE_13__ {TYPE_3__ s3; TYPE_5__* method; } ;
struct TYPE_12__ {TYPE_4__* ssl3_enc; } ;
struct TYPE_11__ {int enc_flags; } ;
struct TYPE_8__ {long algorithm2; int algorithm_mkey; } ;
typedef  TYPE_6__ SSL ;

/* Variables and functions */
 int SSL_ENC_FLAG_SHA256_PRF ; 
 long SSL_HANDSHAKE_MAC_DEFAULT ; 
 long SSL_HANDSHAKE_MAC_SHA256 ; 
 long SSL_HANDSHAKE_MAC_SHA384 ; 
 int SSL_PSK ; 
 long TLS1_PRF ; 
 long TLS1_PRF_SHA256 ; 
 long TLS1_PRF_SHA384 ; 

long ssl_get_algorithm2(SSL *s)
{
    long alg2;
    if (s->s3.tmp.new_cipher == NULL)
        return -1;
    alg2 = s->s3.tmp.new_cipher->algorithm2;
    if (s->method->ssl3_enc->enc_flags & SSL_ENC_FLAG_SHA256_PRF) {
        if (alg2 == (SSL_HANDSHAKE_MAC_DEFAULT | TLS1_PRF))
            return SSL_HANDSHAKE_MAC_SHA256 | TLS1_PRF_SHA256;
    } else if (s->s3.tmp.new_cipher->algorithm_mkey & SSL_PSK) {
        if (alg2 == (SSL_HANDSHAKE_MAC_SHA384 | TLS1_PRF_SHA384))
            return SSL_HANDSHAKE_MAC_DEFAULT | TLS1_PRF;
    }
    return alg2;
}