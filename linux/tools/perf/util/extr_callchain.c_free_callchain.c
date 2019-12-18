#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct callchain_root {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_callchain_node (int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

void free_callchain(struct callchain_root *root)
{
	if (!symbol_conf.use_callchain)
		return;

	free_callchain_node(&root->node);
}