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
typedef  enum smallchoices { ____Placeholder_smallchoices } smallchoices ;
typedef  enum medchoices { ____Placeholder_medchoices } medchoices ;
typedef  enum largechoices { ____Placeholder_largechoices } largechoices ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_size_t_eq (int,int) ; 

__attribute__((used)) static int test_sanity_enum_size(void)
{
    enum smallchoices { sa, sb, sc };
    enum medchoices { ma, mb, mc, md, me, mf, mg, mh, mi, mj, mk, ml };
    enum largechoices {
        a01, b01, c01, d01, e01, f01, g01, h01, i01, j01,
        a02, b02, c02, d02, e02, f02, g02, h02, i02, j02,
        a03, b03, c03, d03, e03, f03, g03, h03, i03, j03,
        a04, b04, c04, d04, e04, f04, g04, h04, i04, j04,
        a05, b05, c05, d05, e05, f05, g05, h05, i05, j05,
        a06, b06, c06, d06, e06, f06, g06, h06, i06, j06,
        a07, b07, c07, d07, e07, f07, g07, h07, i07, j07,
        a08, b08, c08, d08, e08, f08, g08, h08, i08, j08,
        a09, b09, c09, d09, e09, f09, g09, h09, i09, j09,
        a10, b10, c10, d10, e10, f10, g10, h10, i10, j10,
        xxx };

    /* Enum size */
    if (!TEST_size_t_eq(sizeof(enum smallchoices), sizeof(int))
        || !TEST_size_t_eq(sizeof(enum medchoices), sizeof(int))
        || !TEST_size_t_eq(sizeof(enum largechoices), sizeof(int)))
        return 0;
    return 1;
}