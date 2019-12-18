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
typedef  int /*<<< orphan*/  X509_ATTRIBUTE ;
struct TYPE_5__ {void* ptr; } ;
struct TYPE_6__ {TYPE_1__ value; } ;
typedef  TYPE_2__ ASN1_TYPE ;

/* Variables and functions */
 int ASN1_TYPE_get (TYPE_2__*) ; 
 int V_ASN1_BOOLEAN ; 
 int V_ASN1_NULL ; 
 TYPE_2__* X509_ATTRIBUTE_get0_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_F_X509_ATTRIBUTE_GET0_DATA ; 
 int /*<<< orphan*/  X509_R_WRONG_TYPE ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *X509_ATTRIBUTE_get0_data(X509_ATTRIBUTE *attr, int idx,
                               int atrtype, void *data)
{
    ASN1_TYPE *ttmp;
    ttmp = X509_ATTRIBUTE_get0_type(attr, idx);
    if (!ttmp)
        return NULL;
    if (atrtype == V_ASN1_BOOLEAN
            || atrtype == V_ASN1_NULL
            || atrtype != ASN1_TYPE_get(ttmp)) {
        X509err(X509_F_X509_ATTRIBUTE_GET0_DATA, X509_R_WRONG_TYPE);
        return NULL;
    }
    return ttmp->value.ptr;
}