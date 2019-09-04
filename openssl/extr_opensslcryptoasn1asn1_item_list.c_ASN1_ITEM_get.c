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
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  const* ASN1_ITEM_ptr (int /*<<< orphan*/ ) ; 
 size_t OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * asn1_item_list ; 

const ASN1_ITEM *ASN1_ITEM_get(size_t i)
{
    if (i >= OSSL_NELEM(asn1_item_list))
        return NULL;
    return ASN1_ITEM_ptr(asn1_item_list[i]);
}