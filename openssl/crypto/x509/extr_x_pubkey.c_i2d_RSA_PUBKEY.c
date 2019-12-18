#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_8__ {TYPE_1__ pkey; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_I2D_RSA_PUBKEY ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_assign_RSA (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 TYPE_2__* EVP_PKEY_new () ; 
 int i2d_PUBKEY (TYPE_2__*,unsigned char**) ; 

int i2d_RSA_PUBKEY(const RSA *a, unsigned char **pp)
{
    EVP_PKEY *pktmp;
    int ret;
    if (!a)
        return 0;
    pktmp = EVP_PKEY_new();
    if (pktmp == NULL) {
        ASN1err(ASN1_F_I2D_RSA_PUBKEY, ERR_R_MALLOC_FAILURE);
        return -1;
    }
    (void)EVP_PKEY_assign_RSA(pktmp, (RSA *)a);
    ret = i2d_PUBKEY(pktmp, pp);
    pktmp->pkey.ptr = NULL;
    EVP_PKEY_free(pktmp);
    return ret;
}