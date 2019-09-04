#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ameth; } ;
struct TYPE_6__ {int (* pub_print ) (int /*<<< orphan*/ *,TYPE_2__ const*,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,TYPE_2__ const*,int,int /*<<< orphan*/ *) ; 
 int unsup_alg (int /*<<< orphan*/ *,TYPE_2__ const*,int,char*) ; 

int EVP_PKEY_print_public(BIO *out, const EVP_PKEY *pkey,
                          int indent, ASN1_PCTX *pctx)
{
    if (pkey->ameth && pkey->ameth->pub_print)
        return pkey->ameth->pub_print(out, pkey, indent, pctx);

    return unsup_alg(out, pkey, indent, "Public Key");
}