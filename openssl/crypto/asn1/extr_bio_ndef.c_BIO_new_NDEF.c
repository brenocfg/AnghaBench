#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ (* asn1_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_3__ const*,TYPE_2__*) ;} ;
struct TYPE_13__ {TYPE_4__* funcs; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ndef_bio; int /*<<< orphan*/ * boundary; int /*<<< orphan*/ * out; } ;
struct TYPE_11__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * boundary; int /*<<< orphan*/ * ndef_bio; TYPE_3__ const* it; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ NDEF_SUPPORT ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_2__ ASN1_STREAM_ARG ;
typedef  TYPE_3__ ASN1_ITEM ;
typedef  TYPE_4__ ASN1_AUX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_BIO_NEW_NDEF ; 
 int /*<<< orphan*/  ASN1_OP_STREAM_PRE ; 
 int /*<<< orphan*/  ASN1_R_STREAMING_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_C_SET_EX_ARG ; 
 int /*<<< orphan*/  BIO_asn1_set_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_asn1_set_suffix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_f_asn1 () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  ndef_prefix ; 
 int /*<<< orphan*/  ndef_prefix_free ; 
 int /*<<< orphan*/  ndef_suffix ; 
 int /*<<< orphan*/  ndef_suffix_free ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_3__ const*,TYPE_2__*) ; 

BIO *BIO_new_NDEF(BIO *out, ASN1_VALUE *val, const ASN1_ITEM *it)
{
    NDEF_SUPPORT *ndef_aux = NULL;
    BIO *asn_bio = NULL;
    const ASN1_AUX *aux = it->funcs;
    ASN1_STREAM_ARG sarg;

    if (!aux || !aux->asn1_cb) {
        ASN1err(ASN1_F_BIO_NEW_NDEF, ASN1_R_STREAMING_NOT_SUPPORTED);
        return NULL;
    }
    ndef_aux = OPENSSL_zalloc(sizeof(*ndef_aux));
    asn_bio = BIO_new(BIO_f_asn1());
    if (ndef_aux == NULL || asn_bio == NULL)
        goto err;

    /* ASN1 bio needs to be next to output BIO */
    out = BIO_push(asn_bio, out);
    if (out == NULL)
        goto err;

    BIO_asn1_set_prefix(asn_bio, ndef_prefix, ndef_prefix_free);
    BIO_asn1_set_suffix(asn_bio, ndef_suffix, ndef_suffix_free);

    /*
     * Now let callback prepends any digest, cipher etc BIOs ASN1 structure
     * needs.
     */

    sarg.out = out;
    sarg.ndef_bio = NULL;
    sarg.boundary = NULL;

    if (aux->asn1_cb(ASN1_OP_STREAM_PRE, &val, it, &sarg) <= 0)
        goto err;

    ndef_aux->val = val;
    ndef_aux->it = it;
    ndef_aux->ndef_bio = sarg.ndef_bio;
    ndef_aux->boundary = sarg.boundary;
    ndef_aux->out = out;

    BIO_ctrl(asn_bio, BIO_C_SET_EX_ARG, 0, ndef_aux);

    return sarg.ndef_bio;

 err:
    BIO_free(asn_bio);
    OPENSSL_free(ndef_aux);
    return NULL;
}