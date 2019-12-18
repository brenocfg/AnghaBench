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
struct symt {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG64 ;

/* Variables and functions */
 int cmp_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symt_get_address (struct symt const*,int /*<<< orphan*/ *) ; 

int symt_cmp_addr(const void* p1, const void* p2)
{
    const struct symt*  sym1 = *(const struct symt* const *)p1;
    const struct symt*  sym2 = *(const struct symt* const *)p2;
    ULONG64     a1, a2;

    symt_get_address(sym1, &a1);
    symt_get_address(sym2, &a2);
    return cmp_addr(a1, a2);
}