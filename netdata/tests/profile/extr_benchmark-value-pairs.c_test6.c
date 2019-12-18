#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  value; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  ARL_BASE ;

/* Variables and functions */
 int /*<<< orphan*/  arl_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ arl_check (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * arl_create (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arl_expect_custom (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arl_strtoull ; 
 TYPE_1__* pairs ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * values6 ; 

void test6() {
    static ARL_BASE *base = NULL;

    if(unlikely(!base)) {
        base = arl_create("test6", arl_strtoull, 60);
        arl_expect_custom(base, "cache",       NULL, &values6[0]);
        arl_expect_custom(base, "rss",         NULL, &values6[1]);
        arl_expect_custom(base, "rss_huge",    NULL, &values6[2]);
        arl_expect_custom(base, "mapped_file", NULL, &values6[3]);
        arl_expect_custom(base, "writeback",   NULL, &values6[4]);
        arl_expect_custom(base, "dirty",       NULL, &values6[5]);
        arl_expect_custom(base, "swap",        NULL, &values6[6]);
        arl_expect_custom(base, "pgpgin",      NULL, &values6[7]);
        arl_expect_custom(base, "pgpgout",     NULL, &values6[8]);
        arl_expect_custom(base, "pgfault",     NULL, &values6[9]);
        arl_expect_custom(base, "pgmajfault",  NULL, &values6[10]);
    }

    arl_begin(base);

    int i;
    for(i = 0; pairs[i].name ; i++)
        if(arl_check(base, pairs[i].name, pairs[i].value)) break;
}