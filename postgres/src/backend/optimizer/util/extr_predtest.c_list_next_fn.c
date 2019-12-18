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
struct TYPE_3__ {int /*<<< orphan*/  state_list; void* state; } ;
typedef  TYPE_1__* PredIterInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ListCell ;

/* Variables and functions */
 int /*<<< orphan*/ * lfirst (int /*<<< orphan*/ *) ; 
 scalar_t__ lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *
list_next_fn(PredIterInfo info)
{
	ListCell   *l = (ListCell *) info->state;
	Node	   *n;

	if (l == NULL)
		return NULL;
	n = lfirst(l);
	info->state = (void *) lnext(info->state_list, l);
	return n;
}