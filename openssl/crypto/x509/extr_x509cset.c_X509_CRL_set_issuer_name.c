#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_4__ {int /*<<< orphan*/  issuer; } ;
struct TYPE_5__ {TYPE_1__ crl; } ;
typedef  TYPE_2__ X509_CRL ;

/* Variables and functions */
 int X509_NAME_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509_CRL_set_issuer_name(X509_CRL *x, X509_NAME *name)
{
    if (x == NULL)
        return 0;
    return X509_NAME_set(&x->crl.issuer, name);
}