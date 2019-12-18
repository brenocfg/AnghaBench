#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ASN1_TYPE ;
typedef  void ASN1_STRING ;
typedef  void ASN1_OBJECT ;

/* Variables and functions */
 void* ASN1_STRING_dup (void const*) ; 
 int /*<<< orphan*/  ASN1_TYPE_set (int /*<<< orphan*/ *,int,void*) ; 
 void* OBJ_dup (void const*) ; 
 int V_ASN1_BOOLEAN ; 
 int V_ASN1_OBJECT ; 

int ASN1_TYPE_set1(ASN1_TYPE *a, int type, const void *value)
{
    if (!value || (type == V_ASN1_BOOLEAN)) {
        void *p = (void *)value;
        ASN1_TYPE_set(a, type, p);
    } else if (type == V_ASN1_OBJECT) {
        ASN1_OBJECT *odup;
        odup = OBJ_dup(value);
        if (!odup)
            return 0;
        ASN1_TYPE_set(a, type, odup);
    } else {
        ASN1_STRING *sdup;
        sdup = ASN1_STRING_dup(value);
        if (!sdup)
            return 0;
        ASN1_TYPE_set(a, type, sdup);
    }
    return 1;
}