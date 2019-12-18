#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * crl; } ;
struct TYPE_6__ {TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_CRL ;

/* Variables and functions */
 int /*<<< orphan*/  X509_CRL_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_LU_CRL ; 
 int /*<<< orphan*/  x509_object_free_internal (TYPE_2__*) ; 

int X509_OBJECT_set1_X509_CRL(X509_OBJECT *a, X509_CRL *obj)
{
    if (a == NULL || !X509_CRL_up_ref(obj))
        return 0;

    x509_object_free_internal(a);
    a->type = X509_LU_CRL;
    a->data.crl = obj;
    return 1;
}