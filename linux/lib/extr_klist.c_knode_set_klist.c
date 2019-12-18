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
struct klist_node {struct klist* n_klist; } ;
struct klist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knode_dead (struct klist_node*) ; 

__attribute__((used)) static void knode_set_klist(struct klist_node *knode, struct klist *klist)
{
	knode->n_klist = klist;
	/* no knode deserves to start its life dead */
	WARN_ON(knode_dead(knode));
}