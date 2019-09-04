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
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_item_pack (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 

ASN1_TYPE *ASN1_TYPE_pack_sequence(const ASN1_ITEM *it, void *s, ASN1_TYPE **t)
{
    ASN1_OCTET_STRING *oct;
    ASN1_TYPE *rt;

    oct = ASN1_item_pack(s, it, NULL);
    if (oct == NULL)
        return NULL;

    if (t && *t) {
        rt = *t;
    } else {
        rt = ASN1_TYPE_new();
        if (rt == NULL) {
            ASN1_OCTET_STRING_free(oct);
            return NULL;
        }
        if (t)
            *t = rt;
    }
    ASN1_TYPE_set(rt, V_ASN1_SEQUENCE, oct);
    return rt;
}