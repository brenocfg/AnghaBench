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
typedef  int /*<<< orphan*/  ASN1_TLC ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 scalar_t__ ASN1_item_ex_d2i (int /*<<< orphan*/ **,unsigned char const**,long,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asn1_tlc_clear_nc (int /*<<< orphan*/ *) ; 

ASN1_VALUE *ASN1_item_d2i(ASN1_VALUE **pval,
                          const unsigned char **in, long len,
                          const ASN1_ITEM *it)
{
    ASN1_TLC c;
    ASN1_VALUE *ptmpval = NULL;

    if (pval == NULL)
        pval = &ptmpval;
    asn1_tlc_clear_nc(&c);
    if (ASN1_item_ex_d2i(pval, in, len, it, -1, 0, 0, &c) > 0)
        return *pval;
    return NULL;
}