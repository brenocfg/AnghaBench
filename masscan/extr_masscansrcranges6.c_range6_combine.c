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
struct Range6 {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 scalar_t__ LESSEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
range6_combine(struct Range6 *lhs, const struct Range6 rhs)
{
    if (LESSEQ(rhs.begin, lhs->begin))
        lhs->begin = rhs.begin;
    if (LESSEQ(lhs->end, rhs.end))
        lhs->end = rhs.end;
}