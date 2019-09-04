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
typedef  int /*<<< orphan*/  BIT_STRING_BITNAME ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int ASN1_BIT_STRING_num_asc (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_BIT_STRING_set_bit (int /*<<< orphan*/ *,int,int) ; 

int ASN1_BIT_STRING_set_asc(ASN1_BIT_STRING *bs, const char *name, int value,
                            BIT_STRING_BITNAME *tbl)
{
    int bitnum;
    bitnum = ASN1_BIT_STRING_num_asc(name, tbl);
    if (bitnum < 0)
        return 0;
    if (bs) {
        if (!ASN1_BIT_STRING_set_bit(bs, bitnum, value))
            return 0;
    }
    return 1;
}