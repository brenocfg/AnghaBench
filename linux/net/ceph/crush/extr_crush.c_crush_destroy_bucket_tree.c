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
struct TYPE_2__ {struct crush_bucket_tree* items; } ;
struct crush_bucket_tree {struct crush_bucket_tree* node_weights; TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct crush_bucket_tree*) ; 

void crush_destroy_bucket_tree(struct crush_bucket_tree *b)
{
	kfree(b->h.items);
	kfree(b->node_weights);
	kfree(b);
}