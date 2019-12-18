#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_CERT_AUX ;
struct TYPE_3__ {int /*<<< orphan*/ * aux; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/ * X509_CERT_AUX_new () ; 

__attribute__((used)) static X509_CERT_AUX *aux_get(X509 *x)
{
    if (x == NULL)
        return NULL;
    if (x->aux == NULL && (x->aux = X509_CERT_AUX_new()) == NULL)
        return NULL;
    return x->aux;
}