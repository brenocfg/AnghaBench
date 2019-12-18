#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  set; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ X509_ATTRIBUTE ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  X509_ATTRIBUTE_free (TYPE_1__*) ; 
 TYPE_1__* X509_ATTRIBUTE_new () ; 
 int /*<<< orphan*/  sk_ASN1_TYPE_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

X509_ATTRIBUTE *X509_ATTRIBUTE_create(int nid, int atrtype, void *value)
{
    X509_ATTRIBUTE *ret = NULL;
    ASN1_TYPE *val = NULL;

    if ((ret = X509_ATTRIBUTE_new()) == NULL)
        return NULL;
    ret->object = OBJ_nid2obj(nid);
    if ((val = ASN1_TYPE_new()) == NULL)
        goto err;
    if (!sk_ASN1_TYPE_push(ret->set, val))
        goto err;

    ASN1_TYPE_set(val, atrtype, value);
    return ret;
 err:
    X509_ATTRIBUTE_free(ret);
    ASN1_TYPE_free(val);
    return NULL;
}