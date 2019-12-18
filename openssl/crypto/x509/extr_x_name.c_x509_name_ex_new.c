#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int modified; int /*<<< orphan*/ * entries; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_1__ X509_NAME ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_X509_NAME_EX_NEW ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BUF_MEM_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  sk_X509_NAME_ENTRY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_NAME_ENTRY_new_null () ; 

__attribute__((used)) static int x509_name_ex_new(ASN1_VALUE **val, const ASN1_ITEM *it)
{
    X509_NAME *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL)
        goto memerr;
    if ((ret->entries = sk_X509_NAME_ENTRY_new_null()) == NULL)
        goto memerr;
    if ((ret->bytes = BUF_MEM_new()) == NULL)
        goto memerr;
    ret->modified = 1;
    *val = (ASN1_VALUE *)ret;
    return 1;

 memerr:
    ASN1err(ASN1_F_X509_NAME_EX_NEW, ERR_R_MALLOC_FAILURE);
    if (ret) {
        sk_X509_NAME_ENTRY_free(ret->entries);
        OPENSSL_free(ret);
    }
    return 0;
}