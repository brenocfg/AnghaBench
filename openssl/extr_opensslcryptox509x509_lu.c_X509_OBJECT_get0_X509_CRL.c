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
struct TYPE_4__ {int /*<<< orphan*/ * crl; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ data; } ;
typedef  TYPE_2__ X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_CRL ;

/* Variables and functions */
 scalar_t__ X509_LU_CRL ; 

X509_CRL *X509_OBJECT_get0_X509_CRL(X509_OBJECT *a)
{
    if (a == NULL || a->type != X509_LU_CRL)
        return NULL;
    return a->data.crl;
}