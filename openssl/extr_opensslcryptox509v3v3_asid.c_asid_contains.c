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
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASIdOrRanges ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_min_max (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int sk_ASIdOrRange_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_ASIdOrRange_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int asid_contains(ASIdOrRanges *parent, ASIdOrRanges *child)
{
    ASN1_INTEGER *p_min = NULL, *p_max = NULL, *c_min = NULL, *c_max = NULL;
    int p, c;

    if (child == NULL || parent == child)
        return 1;
    if (parent == NULL)
        return 0;

    p = 0;
    for (c = 0; c < sk_ASIdOrRange_num(child); c++) {
        if (!extract_min_max(sk_ASIdOrRange_value(child, c), &c_min, &c_max))
            return 0;
        for (;; p++) {
            if (p >= sk_ASIdOrRange_num(parent))
                return 0;
            if (!extract_min_max(sk_ASIdOrRange_value(parent, p), &p_min,
                                 &p_max))
                return 0;
            if (ASN1_INTEGER_cmp(p_max, c_max) < 0)
                continue;
            if (ASN1_INTEGER_cmp(p_min, c_min) > 0)
                return 0;
            break;
        }
    }

    return 1;
}