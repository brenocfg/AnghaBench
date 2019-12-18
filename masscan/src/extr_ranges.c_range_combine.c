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
struct Range {scalar_t__ begin; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static void
range_combine(struct Range *lhs, struct Range rhs)
{
    if (lhs->begin > rhs.begin)
        lhs->begin = rhs.begin;
    if (lhs->end < rhs.end)
        lhs->end = rhs.end;
}