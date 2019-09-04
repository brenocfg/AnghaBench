#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hi; scalar_t__ lo; } ;
typedef  TYPE_1__ ipv6address ;

/* Variables and functions */

__attribute__((used)) static int
LESSEQ(const ipv6address lhs, const ipv6address rhs)
{
    if (lhs.hi <= rhs.hi)
        return 1;
    else if (lhs.hi == rhs.hi && lhs.lo <= rhs.lo)
        return 1;
    else
        return 0;
}