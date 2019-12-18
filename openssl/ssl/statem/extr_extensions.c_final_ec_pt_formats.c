#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ecpointformats_len; unsigned char* peer_ecpointformats; scalar_t__ peer_ecpointformats_len; int /*<<< orphan*/ * ecpointformats; } ;
struct TYPE_9__ {TYPE_1__* new_cipher; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
struct TYPE_12__ {TYPE_4__ ext; TYPE_3__ s3; scalar_t__ server; } ;
struct TYPE_8__ {unsigned long algorithm_mkey; unsigned long algorithm_auth; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_F_FINAL_EC_PT_FORMATS ; 
 int /*<<< orphan*/  SSL_R_TLS_INVALID_ECPOINTFORMAT_LIST ; 
 unsigned long SSL_aECDSA ; 
 unsigned long SSL_kECDHE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_ECPOINTFORMAT_uncompressed ; 

__attribute__((used)) static int final_ec_pt_formats(SSL *s, unsigned int context, int sent)
{
    unsigned long alg_k, alg_a;

    if (s->server)
        return 1;

    alg_k = s->s3.tmp.new_cipher->algorithm_mkey;
    alg_a = s->s3.tmp.new_cipher->algorithm_auth;

    /*
     * If we are client and using an elliptic curve cryptography cipher
     * suite, then if server returns an EC point formats lists extension it
     * must contain uncompressed.
     */
    if (s->ext.ecpointformats != NULL
            && s->ext.ecpointformats_len > 0
            && s->ext.peer_ecpointformats != NULL
            && s->ext.peer_ecpointformats_len > 0
            && ((alg_k & SSL_kECDHE) || (alg_a & SSL_aECDSA))) {
        /* we are using an ECC cipher */
        size_t i;
        unsigned char *list = s->ext.peer_ecpointformats;

        for (i = 0; i < s->ext.peer_ecpointformats_len; i++) {
            if (*list++ == TLSEXT_ECPOINTFORMAT_uncompressed)
                break;
        }
        if (i == s->ext.peer_ecpointformats_len) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_FINAL_EC_PT_FORMATS,
                     SSL_R_TLS_INVALID_ECPOINTFORMAT_LIST);
            return 0;
        }
    }

    return 1;
}