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
struct TYPE_5__ {TYPE_1__* aux; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_4__ {int /*<<< orphan*/ * reject; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void X509_reject_clear(X509 *x)
{
    if (x->aux) {
        sk_ASN1_OBJECT_pop_free(x->aux->reject, ASN1_OBJECT_free);
        x->aux->reject = NULL;
    }
}