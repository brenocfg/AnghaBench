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
struct klist_node {int /*<<< orphan*/  n_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  klist_release ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int klist_dec_and_del(struct klist_node *n)
{
	return kref_put(&n->n_ref, klist_release);
}