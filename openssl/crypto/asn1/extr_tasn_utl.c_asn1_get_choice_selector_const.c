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
struct TYPE_3__ {int /*<<< orphan*/  utype; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_ITEM ;

/* Variables and functions */
 int* offset2ptr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int asn1_get_choice_selector_const(const ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    int *sel = offset2ptr(*pval, it->utype);

    return *sel;
}