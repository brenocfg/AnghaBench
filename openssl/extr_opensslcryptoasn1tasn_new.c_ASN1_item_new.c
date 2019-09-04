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
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 scalar_t__ ASN1_item_ex_new (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 

ASN1_VALUE *ASN1_item_new(const ASN1_ITEM *it)
{
    ASN1_VALUE *ret = NULL;
    if (ASN1_item_ex_new(&ret, it) > 0)
        return ret;
    return NULL;
}