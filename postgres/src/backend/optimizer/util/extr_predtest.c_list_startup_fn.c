#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * state_list; void* state; } ;
typedef  TYPE_1__* PredIterInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ list_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
list_startup_fn(Node *clause, PredIterInfo info)
{
	info->state_list = (List *) clause;
	info->state = (void *) list_head(info->state_list);
}