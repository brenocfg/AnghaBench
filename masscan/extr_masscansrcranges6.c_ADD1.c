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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ lo; int /*<<< orphan*/  hi; } ;
typedef  TYPE_1__ ipv6address ;

/* Variables and functions */

__attribute__((used)) static ipv6address ADD1(const ipv6address lhs, uint64_t rhs)
{
    ipv6address result = lhs;
    result.lo += rhs;
    if (result.lo < lhs.lo)
        result.hi++;
    return result;
}