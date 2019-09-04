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
struct Range6List {int dummy; } ;
struct Range6 {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  range6list_remove_range (struct Range6List*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
range6list_remove_range2(struct Range6List *targets, struct Range6 range)
{
    range6list_remove_range(targets, range.begin, range.end);
}