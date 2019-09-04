#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sname; } ;
typedef  TYPE_1__ ASN1_ITEM ;

/* Variables and functions */
 TYPE_1__* ASN1_ITEM_ptr (int /*<<< orphan*/ ) ; 
 size_t OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * asn1_item_list ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

const ASN1_ITEM *ASN1_ITEM_lookup(const char *name)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(asn1_item_list); i++) {
        const ASN1_ITEM *it = ASN1_ITEM_ptr(asn1_item_list[i]);

        if (strcmp(it->sname, name) == 0)
            return it;
    }
    return NULL;
}