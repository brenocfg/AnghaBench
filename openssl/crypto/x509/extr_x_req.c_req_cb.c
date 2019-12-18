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
struct TYPE_2__ {int /*<<< orphan*/ * sm2_id; } ;
typedef  TYPE_1__ X509_REQ ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
#define  ASN1_OP_D2I_PRE 130 
#define  ASN1_OP_FREE_POST 129 
#define  ASN1_OP_NEW_POST 128 

__attribute__((used)) static int req_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                  void *exarg)
{
#ifndef OPENSSL_NO_SM2
    X509_REQ *ret = (X509_REQ *)*pval;

    switch (operation) {
    case ASN1_OP_D2I_PRE:
        ASN1_OCTET_STRING_free(ret->sm2_id);
        /* fall thru */
    case ASN1_OP_NEW_POST:
        ret->sm2_id = NULL;
        break;

    case ASN1_OP_FREE_POST:
        ASN1_OCTET_STRING_free(ret->sm2_id);
        break;
    }
#endif

    return 1;
}