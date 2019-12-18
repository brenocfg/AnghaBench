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
struct TYPE_3__ {int flags; int /*<<< orphan*/  item; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_TEMPLATE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_ptr (int /*<<< orphan*/ ) ; 
 int ASN1_TFLG_ADB_MASK ; 
 int ASN1_TFLG_SK_MASK ; 
 int /*<<< orphan*/  asn1_item_clear (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asn1_template_clear(ASN1_VALUE **pval, const ASN1_TEMPLATE *tt)
{
    /* If ADB or STACK just NULL the field */
    if (tt->flags & (ASN1_TFLG_ADB_MASK | ASN1_TFLG_SK_MASK))
        *pval = NULL;
    else
        asn1_item_clear(pval, ASN1_ITEM_ptr(tt->item));
}