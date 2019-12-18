#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* rsa; } ;
struct TYPE_9__ {TYPE_2__* ameth; TYPE_1__ pkey; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pss; } ;
struct TYPE_7__ {scalar_t__ pkey_id; } ;
typedef  TYPE_3__ RSA ;
typedef  TYPE_4__ EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ASN1_item_pack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 int /*<<< orphan*/  RSA_PSS_PARAMS ; 
 int V_ASN1_NULL ; 
 int V_ASN1_SEQUENCE ; 
 int V_ASN1_UNDEF ; 

__attribute__((used)) static int rsa_param_encode(const EVP_PKEY *pkey,
                            ASN1_STRING **pstr, int *pstrtype)
{
    const RSA *rsa = pkey->pkey.rsa;

    *pstr = NULL;
    /* If RSA it's just NULL type */
    if (pkey->ameth->pkey_id != EVP_PKEY_RSA_PSS) {
        *pstrtype = V_ASN1_NULL;
        return 1;
    }
    /* If no PSS parameters we omit parameters entirely */
    if (rsa->pss == NULL) {
        *pstrtype = V_ASN1_UNDEF;
        return 1;
    }
    /* Encode PSS parameters */
    if (ASN1_item_pack(rsa->pss, ASN1_ITEM_rptr(RSA_PSS_PARAMS), pstr) == NULL)
        return 0;

    *pstrtype = V_ASN1_SEQUENCE;
    return 1;
}