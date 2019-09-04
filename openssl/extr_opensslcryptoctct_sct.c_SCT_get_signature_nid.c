#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ version; scalar_t__ hash_alg; int sig_alg; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int NID_ecdsa_with_SHA256 ; 
 int NID_sha256WithRSAEncryption ; 
 int NID_undef ; 
 scalar_t__ SCT_VERSION_V1 ; 
 scalar_t__ TLSEXT_hash_sha256 ; 
#define  TLSEXT_signature_ecdsa 129 
#define  TLSEXT_signature_rsa 128 

int SCT_get_signature_nid(const SCT *sct)
{
    if (sct->version == SCT_VERSION_V1) {
        if (sct->hash_alg == TLSEXT_hash_sha256) {
            switch (sct->sig_alg) {
            case TLSEXT_signature_ecdsa:
                return NID_ecdsa_with_SHA256;
            case TLSEXT_signature_rsa:
                return NID_sha256WithRSAEncryption;
            default:
                return NID_undef;
            }
        }
    }
    return NID_undef;
}