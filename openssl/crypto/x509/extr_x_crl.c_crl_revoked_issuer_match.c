#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  issuer; } ;
typedef  TYPE_2__ X509_REVOKED ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509_CRL ;
struct TYPE_6__ {int /*<<< orphan*/ * directoryName; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  TYPE_3__ GENERAL_NAME ;

/* Variables and functions */
 scalar_t__ GEN_DIRNAME ; 
 int /*<<< orphan*/ * X509_CRL_get_issuer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_GENERAL_NAME_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crl_revoked_issuer_match(X509_CRL *crl, X509_NAME *nm,
                                    X509_REVOKED *rev)
{
    int i;

    if (!rev->issuer) {
        if (!nm)
            return 1;
        if (!X509_NAME_cmp(nm, X509_CRL_get_issuer(crl)))
            return 1;
        return 0;
    }

    if (!nm)
        nm = X509_CRL_get_issuer(crl);

    for (i = 0; i < sk_GENERAL_NAME_num(rev->issuer); i++) {
        GENERAL_NAME *gen = sk_GENERAL_NAME_value(rev->issuer, i);
        if (gen->type != GEN_DIRNAME)
            continue;
        if (!X509_NAME_cmp(nm, gen->d.directoryName))
            return 1;
    }
    return 0;

}