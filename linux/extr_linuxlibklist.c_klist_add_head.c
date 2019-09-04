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
struct klist_node {int dummy; } ;
struct klist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_head (struct klist*,struct klist_node*) ; 
 int /*<<< orphan*/  klist_node_init (struct klist*,struct klist_node*) ; 

void klist_add_head(struct klist_node *n, struct klist *k)
{
	klist_node_init(k, n);
	add_head(k, n);
}