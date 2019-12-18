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
struct Range6 {int /*<<< orphan*/  begin; int /*<<< orphan*/  end; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ const ipv6address ;

/* Variables and functions */
 scalar_t__ LESS (TYPE_1__ const,int /*<<< orphan*/ ) ; 
 TYPE_1__ const MINUS_ONE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
range6_is_overlap(const struct Range6 lhs, const struct Range6 rhs)
{
    static const ipv6address zero = {0, 0};
    ipv6address lhs_endm = MINUS_ONE(lhs.end);
    ipv6address rhs_endm = MINUS_ONE(rhs.end);
    
    /* llll rrrr */
    if (LESS(zero, lhs.end) && LESS(lhs_endm, rhs.begin))
        return 0;

    /* rrrr llll */
    if (LESS(zero, rhs.end) && LESS(rhs_endm, lhs.begin))
        return 0;

    return 1;
}