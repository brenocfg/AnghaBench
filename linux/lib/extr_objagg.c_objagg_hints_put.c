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
struct objagg_hints {int /*<<< orphan*/  node_ht; scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct objagg_hints*) ; 
 int /*<<< orphan*/  objagg_hints_flush (struct objagg_hints*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void objagg_hints_put(struct objagg_hints *objagg_hints)
{
	if (--objagg_hints->refcount)
		return;
	objagg_hints_flush(objagg_hints);
	rhashtable_destroy(&objagg_hints->node_ht);
	kfree(objagg_hints);
}