#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_5__ {int /*<<< orphan*/  req_info; int /*<<< orphan*/  signature; TYPE_4__ sig_alg; } ;
typedef  TYPE_1__ X509_REQ ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_R_UNKNOWN_SIGNATURE_ALGORITHM ; 
 int ASN1_item_verify (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NID_sm2 ; 
 int /*<<< orphan*/  OBJ_find_sigid_algs (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_F_X509_REQ_VERIFY ; 
 int /*<<< orphan*/  X509_REQ_INFO ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int x509_req_verify_sm2 (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

int X509_REQ_verify(X509_REQ *a, EVP_PKEY *r)
{
#ifndef OPENSSL_NO_SM2
    int mdnid, pknid;

    /* Convert signature OID into digest and public key OIDs */
    if (!OBJ_find_sigid_algs(OBJ_obj2nid(a->sig_alg.algorithm),
                             &mdnid, &pknid)) {
        X509err(X509_F_X509_REQ_VERIFY, ASN1_R_UNKNOWN_SIGNATURE_ALGORITHM);
        return 0;
    }

    if (pknid == NID_sm2)
        return x509_req_verify_sm2(a, r, mdnid, pknid);
#endif

    return (ASN1_item_verify(ASN1_ITEM_rptr(X509_REQ_INFO),
                             &a->sig_alg, a->signature, &a->req_info, r));
}