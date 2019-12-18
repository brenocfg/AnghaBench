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
struct Range6List {scalar_t__ picker; scalar_t__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct Range6List*,int /*<<< orphan*/ ,int) ; 

void
range6list_remove_all(struct Range6List *targets)
{
    if (targets->list)
        free(targets->list);
    if (targets->picker)
        free(targets->picker);
    memset(targets, 0, sizeof(*targets));
}