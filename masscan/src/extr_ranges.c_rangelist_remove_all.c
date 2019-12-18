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
struct RangeList {int /*<<< orphan*/  picker; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct RangeList*,int /*<<< orphan*/ ,int) ; 

void
rangelist_remove_all(struct RangeList *targets)
{
    free(targets->list);
    free(targets->picker);
    memset(targets, 0, sizeof(*targets));
}