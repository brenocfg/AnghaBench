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
struct TYPE_3__ {void* validation_status; int /*<<< orphan*/  sig_alg; void* hash_alg; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_SET_SIGNATURE_NID ; 
 int /*<<< orphan*/  CT_R_UNRECOGNIZED_SIGNATURE_NID ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_ecdsa_with_SHA256 129 
#define  NID_sha256WithRSAEncryption 128 
 void* SCT_VALIDATION_STATUS_NOT_SET ; 
 void* TLSEXT_hash_sha256 ; 
 int /*<<< orphan*/  TLSEXT_signature_ecdsa ; 
 int /*<<< orphan*/  TLSEXT_signature_rsa ; 

int SCT_set_signature_nid(SCT *sct, int nid)
{
    switch (nid) {
    case NID_sha256WithRSAEncryption:
        sct->hash_alg = TLSEXT_hash_sha256;
        sct->sig_alg = TLSEXT_signature_rsa;
        sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;
        return 1;
    case NID_ecdsa_with_SHA256:
        sct->hash_alg = TLSEXT_hash_sha256;
        sct->sig_alg = TLSEXT_signature_ecdsa;
        sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;
        return 1;
    default:
        CTerr(CT_F_SCT_SET_SIGNATURE_NID, CT_R_UNRECOGNIZED_SIGNATURE_NID);
        return 0;
    }
}