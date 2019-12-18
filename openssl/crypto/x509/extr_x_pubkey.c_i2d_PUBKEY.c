#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* pkey; } ;
typedef  TYPE_2__ X509_PUBKEY ;
struct TYPE_12__ {TYPE_1__* ameth; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* pub_encode ) (TYPE_2__*,TYPE_3__ const*) ;} ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  X509_PUBKEY_free (TYPE_2__*) ; 
 TYPE_2__* X509_PUBKEY_new () ; 
 int i2d_X509_PUBKEY (TYPE_2__*,unsigned char**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__ const*) ; 

int i2d_PUBKEY(const EVP_PKEY *a, unsigned char **pp)
{
    X509_PUBKEY *xpk = NULL;
    int ret = -1;

    if (a == NULL)
        return 0;
    if ((xpk = X509_PUBKEY_new()) == NULL)
        return -1;
    if (a->ameth != NULL && a->ameth->pub_encode != NULL
        && !a->ameth->pub_encode(xpk, a))
        goto error;
    xpk->pkey = (EVP_PKEY *)a;
    ret = i2d_X509_PUBKEY(xpk, pp);
    xpk->pkey = NULL;
 error:
    X509_PUBKEY_free(xpk);
    return ret;
}