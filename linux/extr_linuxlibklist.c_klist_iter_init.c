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
struct klist_iter {int dummy; } ;
struct klist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  klist_iter_init_node (struct klist*,struct klist_iter*,int /*<<< orphan*/ *) ; 

void klist_iter_init(struct klist *k, struct klist_iter *i)
{
	klist_iter_init_node(k, i, NULL);
}