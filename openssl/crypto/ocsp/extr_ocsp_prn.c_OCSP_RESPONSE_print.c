#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* revoked; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_2__ value; } ;
struct TYPE_24__ {int /*<<< orphan*/  responseType; } ;
struct TYPE_17__ {int /*<<< orphan*/  byKey; int /*<<< orphan*/  byName; } ;
struct TYPE_22__ {int type; TYPE_1__ value; } ;
struct TYPE_23__ {int /*<<< orphan*/  responseExtensions; int /*<<< orphan*/  responses; scalar_t__ producedAt; TYPE_6__ responderId; int /*<<< orphan*/  version; } ;
struct TYPE_21__ {scalar_t__ responseStatus; TYPE_8__* responseBytes; } ;
struct TYPE_20__ {scalar_t__ revocationReason; scalar_t__ revocationTime; } ;
struct TYPE_19__ {int /*<<< orphan*/  singleExtensions; scalar_t__ nextUpdate; scalar_t__ thisUpdate; TYPE_9__* certStatus; int /*<<< orphan*/ * certId; } ;
struct TYPE_16__ {int /*<<< orphan*/  certs; int /*<<< orphan*/  signature; int /*<<< orphan*/  signatureAlgorithm; TYPE_7__ tbsResponseData; } ;
typedef  TYPE_3__ OCSP_SINGLERESP ;
typedef  TYPE_4__ OCSP_REVOKEDINFO ;
typedef  TYPE_5__ OCSP_RESPONSE ;
typedef  TYPE_6__ OCSP_RESPID ;
typedef  TYPE_7__ OCSP_RESPDATA ;
typedef  TYPE_8__ OCSP_RESPBYTES ;
typedef  TYPE_9__ OCSP_CERTSTATUS ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;
typedef  TYPE_10__ OCSP_BASICRESP ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long ASN1_ENUMERATED_get (scalar_t__) ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_print (int /*<<< orphan*/ *,scalar_t__) ; 
 long ASN1_INTEGER_get (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ NID_id_pkix_OCSP_basic ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCSP_BASICRESP_free (TYPE_10__*) ; 
 int /*<<< orphan*/  OCSP_cert_status_str (scalar_t__) ; 
 int /*<<< orphan*/  OCSP_crl_reason_str (long) ; 
 TYPE_10__* OCSP_response_get1_basic (TYPE_5__*) ; 
 int /*<<< orphan*/  OCSP_response_status_str (long) ; 
 int /*<<< orphan*/  PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ V_OCSP_CERTSTATUS_REVOKED ; 
#define  V_OCSP_RESPID_KEY 129 
#define  V_OCSP_RESPID_NAME 128 
 int /*<<< orphan*/  X509V3_extensions_print (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ X509_signature_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_ONELINE ; 
 scalar_t__ i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2a_ASN1_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocsp_certid_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sk_OCSP_SINGLERESP_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_OCSP_SINGLERESP_value (int /*<<< orphan*/ ,int) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_value (int /*<<< orphan*/ ,int) ; 

int OCSP_RESPONSE_print(BIO *bp, OCSP_RESPONSE *o, unsigned long flags)
{
    int i, ret = 0;
    long l;
    OCSP_CERTID *cid = NULL;
    OCSP_BASICRESP *br = NULL;
    OCSP_RESPID *rid = NULL;
    OCSP_RESPDATA *rd = NULL;
    OCSP_CERTSTATUS *cst = NULL;
    OCSP_REVOKEDINFO *rev = NULL;
    OCSP_SINGLERESP *single = NULL;
    OCSP_RESPBYTES *rb = o->responseBytes;

    if (BIO_puts(bp, "OCSP Response Data:\n") <= 0)
        goto err;
    l = ASN1_ENUMERATED_get(o->responseStatus);
    if (BIO_printf(bp, "    OCSP Response Status: %s (0x%lx)\n",
                   OCSP_response_status_str(l), l) <= 0)
        goto err;
    if (rb == NULL)
        return 1;
    if (BIO_puts(bp, "    Response Type: ") <= 0)
        goto err;
    if (i2a_ASN1_OBJECT(bp, rb->responseType) <= 0)
        goto err;
    if (OBJ_obj2nid(rb->responseType) != NID_id_pkix_OCSP_basic) {
        BIO_puts(bp, " (unknown response type)\n");
        return 1;
    }

    if ((br = OCSP_response_get1_basic(o)) == NULL)
        goto err;
    rd = &br->tbsResponseData;
    l = ASN1_INTEGER_get(rd->version);
    if (BIO_printf(bp, "\n    Version: %lu (0x%lx)\n", l + 1, l) <= 0)
        goto err;
    if (BIO_puts(bp, "    Responder Id: ") <= 0)
        goto err;

    rid = &rd->responderId;
    switch (rid->type) {
    case V_OCSP_RESPID_NAME:
        X509_NAME_print_ex(bp, rid->value.byName, 0, XN_FLAG_ONELINE);
        break;
    case V_OCSP_RESPID_KEY:
        i2a_ASN1_STRING(bp, rid->value.byKey, 0);
        break;
    }

    if (BIO_printf(bp, "\n    Produced At: ") <= 0)
        goto err;
    if (!ASN1_GENERALIZEDTIME_print(bp, rd->producedAt))
        goto err;
    if (BIO_printf(bp, "\n    Responses:\n") <= 0)
        goto err;
    for (i = 0; i < sk_OCSP_SINGLERESP_num(rd->responses); i++) {
        if (!sk_OCSP_SINGLERESP_value(rd->responses, i))
            continue;
        single = sk_OCSP_SINGLERESP_value(rd->responses, i);
        cid = single->certId;
        if (ocsp_certid_print(bp, cid, 4) <= 0)
            goto err;
        cst = single->certStatus;
        if (BIO_printf(bp, "    Cert Status: %s",
                       OCSP_cert_status_str(cst->type)) <= 0)
            goto err;
        if (cst->type == V_OCSP_CERTSTATUS_REVOKED) {
            rev = cst->value.revoked;
            if (BIO_printf(bp, "\n    Revocation Time: ") <= 0)
                goto err;
            if (!ASN1_GENERALIZEDTIME_print(bp, rev->revocationTime))
                goto err;
            if (rev->revocationReason) {
                l = ASN1_ENUMERATED_get(rev->revocationReason);
                if (BIO_printf(bp,
                               "\n    Revocation Reason: %s (0x%lx)",
                               OCSP_crl_reason_str(l), l) <= 0)
                    goto err;
            }
        }
        if (BIO_printf(bp, "\n    This Update: ") <= 0)
            goto err;
        if (!ASN1_GENERALIZEDTIME_print(bp, single->thisUpdate))
            goto err;
        if (single->nextUpdate) {
            if (BIO_printf(bp, "\n    Next Update: ") <= 0)
                goto err;
            if (!ASN1_GENERALIZEDTIME_print(bp, single->nextUpdate))
                goto err;
        }
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
        if (!X509V3_extensions_print(bp,
                                     "Response Single Extensions",
                                     single->singleExtensions, flags, 8))
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    if (!X509V3_extensions_print(bp, "Response Extensions",
                                 rd->responseExtensions, flags, 4))
        goto err;
    if (X509_signature_print(bp, &br->signatureAlgorithm, br->signature) <= 0)
        goto err;

    for (i = 0; i < sk_X509_num(br->certs); i++) {
        X509_print(bp, sk_X509_value(br->certs, i));
        PEM_write_bio_X509(bp, sk_X509_value(br->certs, i));
    }

    ret = 1;
 err:
    OCSP_BASICRESP_free(br);
    return ret;
}