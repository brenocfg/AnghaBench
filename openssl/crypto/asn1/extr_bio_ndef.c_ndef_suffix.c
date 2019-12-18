#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {scalar_t__ (* asn1_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ;} ;
struct TYPE_8__ {unsigned char** boundary; int /*<<< orphan*/  out; int /*<<< orphan*/  ndef_bio; } ;
struct TYPE_7__ {unsigned char** boundary; unsigned char* derbuf; TYPE_4__* it; int /*<<< orphan*/  val; int /*<<< orphan*/  out; int /*<<< orphan*/  ndef_bio; } ;
typedef  TYPE_1__ NDEF_SUPPORT ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_2__ ASN1_STREAM_ARG ;
typedef  TYPE_3__ ASN1_AUX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_NDEF_SUFFIX ; 
 int /*<<< orphan*/  ASN1_OP_STREAM_POST ; 
 int ASN1_item_ndef_i2d (int /*<<< orphan*/ ,unsigned char**,TYPE_4__*) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned char* OPENSSL_malloc (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static int ndef_suffix(BIO *b, unsigned char **pbuf, int *plen, void *parg)
{
    NDEF_SUPPORT *ndef_aux;
    unsigned char *p;
    int derlen;
    const ASN1_AUX *aux;
    ASN1_STREAM_ARG sarg;

    if (parg == NULL)
        return 0;

    ndef_aux = *(NDEF_SUPPORT **)parg;

    aux = ndef_aux->it->funcs;

    /* Finalize structures */
    sarg.ndef_bio = ndef_aux->ndef_bio;
    sarg.out = ndef_aux->out;
    sarg.boundary = ndef_aux->boundary;
    if (aux->asn1_cb(ASN1_OP_STREAM_POST,
                     &ndef_aux->val, ndef_aux->it, &sarg) <= 0)
        return 0;

    derlen = ASN1_item_ndef_i2d(ndef_aux->val, NULL, ndef_aux->it);
    if (derlen < 0)
        return 0;
    if ((p = OPENSSL_malloc(derlen)) == NULL) {
        ASN1err(ASN1_F_NDEF_SUFFIX, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    ndef_aux->derbuf = p;
    *pbuf = p;
    derlen = ASN1_item_ndef_i2d(ndef_aux->val, &p, ndef_aux->it);

    if (*ndef_aux->boundary == NULL)
        return 0;
    *pbuf = *ndef_aux->boundary;
    *plen = derlen - (*ndef_aux->boundary - ndef_aux->derbuf);

    return 1;
}