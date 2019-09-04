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
typedef  int /*<<< orphan*/  IPAddressOrRanges ;

/* Variables and functions */
 int ADDR_RAW_BUF_LEN ; 
 int /*<<< orphan*/  extract_min_max (int /*<<< orphan*/ ,unsigned char*,unsigned char*,int) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int sk_IPAddressOrRange_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_IPAddressOrRange_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int addr_contains(IPAddressOrRanges *parent,
                         IPAddressOrRanges *child, int length)
{
    unsigned char p_min[ADDR_RAW_BUF_LEN], p_max[ADDR_RAW_BUF_LEN];
    unsigned char c_min[ADDR_RAW_BUF_LEN], c_max[ADDR_RAW_BUF_LEN];
    int p, c;

    if (child == NULL || parent == child)
        return 1;
    if (parent == NULL)
        return 0;

    p = 0;
    for (c = 0; c < sk_IPAddressOrRange_num(child); c++) {
        if (!extract_min_max(sk_IPAddressOrRange_value(child, c),
                             c_min, c_max, length))
            return -1;
        for (;; p++) {
            if (p >= sk_IPAddressOrRange_num(parent))
                return 0;
            if (!extract_min_max(sk_IPAddressOrRange_value(parent, p),
                                 p_min, p_max, length))
                return 0;
            if (memcmp(p_max, c_max, length) < 0)
                continue;
            if (memcmp(p_min, c_min, length) > 0)
                return 0;
            break;
        }
    }

    return 1;
}