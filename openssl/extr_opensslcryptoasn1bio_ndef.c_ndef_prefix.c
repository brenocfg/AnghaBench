#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* derbuf; unsigned char** boundary; int /*<<< orphan*/  it; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ NDEF_SUPPORT ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_NDEF_PREFIX ; 
 int ASN1_item_ndef_i2d (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned char* OPENSSL_malloc (int) ; 

__attribute__((used)) static int ndef_prefix(BIO *b, unsigned char **pbuf, int *plen, void *parg)
{
    NDEF_SUPPORT *ndef_aux;
    unsigned char *p;
    int derlen;

    if (!parg)
        return 0;

    ndef_aux = *(NDEF_SUPPORT **)parg;

    derlen = ASN1_item_ndef_i2d(ndef_aux->val, NULL, ndef_aux->it);
    if ((p = OPENSSL_malloc(derlen)) == NULL) {
        ASN1err(ASN1_F_NDEF_PREFIX, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    ndef_aux->derbuf = p;
    *pbuf = p;
    derlen = ASN1_item_ndef_i2d(ndef_aux->val, &p, ndef_aux->it);

    if (!*ndef_aux->boundary)
        return 0;

    *plen = *ndef_aux->boundary - *pbuf;

    return 1;
}