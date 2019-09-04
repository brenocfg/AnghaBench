#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ (* asn1_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_2__ const*,TYPE_1__*) ;} ;
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ndef_bio; int /*<<< orphan*/ * boundary; int /*<<< orphan*/ * out; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_STREAM_ARG ;
typedef  TYPE_2__ ASN1_ITEM ;
typedef  TYPE_3__ ASN1_AUX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_OUTPUT_DATA ; 
 int /*<<< orphan*/  ASN1_OP_DETACHED_POST ; 
 int /*<<< orphan*/  ASN1_OP_DETACHED_PRE ; 
 int /*<<< orphan*/  ASN1_R_STREAMING_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 
 int PKCS7_REUSE_DIGEST ; 
 int SMIME_DETACHED ; 
 int /*<<< orphan*/  SMIME_crlf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_2__ const*,TYPE_1__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_2__ const*,TYPE_1__*) ; 

__attribute__((used)) static int asn1_output_data(BIO *out, BIO *data, ASN1_VALUE *val, int flags,
                            const ASN1_ITEM *it)
{
    BIO *tmpbio;
    const ASN1_AUX *aux = it->funcs;
    ASN1_STREAM_ARG sarg;
    int rv = 1;

    /*
     * If data is not detached or resigning then the output BIO is already
     * set up to finalise when it is written through.
     */
    if (!(flags & SMIME_DETACHED) || (flags & PKCS7_REUSE_DIGEST)) {
        SMIME_crlf_copy(data, out, flags);
        return 1;
    }

    if (!aux || !aux->asn1_cb) {
        ASN1err(ASN1_F_ASN1_OUTPUT_DATA, ASN1_R_STREAMING_NOT_SUPPORTED);
        return 0;
    }

    sarg.out = out;
    sarg.ndef_bio = NULL;
    sarg.boundary = NULL;

    /* Let ASN1 code prepend any needed BIOs */

    if (aux->asn1_cb(ASN1_OP_DETACHED_PRE, &val, it, &sarg) <= 0)
        return 0;

    /* Copy data across, passing through filter BIOs for processing */
    SMIME_crlf_copy(data, sarg.ndef_bio, flags);

    /* Finalize structure */
    if (aux->asn1_cb(ASN1_OP_DETACHED_POST, &val, it, &sarg) <= 0)
        rv = 0;

    /* Now remove any digests prepended to the BIO */

    while (sarg.ndef_bio != out) {
        tmpbio = BIO_pop(sarg.ndef_bio);
        BIO_free(sarg.ndef_bio);
        sarg.ndef_bio = tmpbio;
    }

    return rv;

}