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
struct btree_head {scalar_t__ height; int /*<<< orphan*/ * node; } ;

/* Variables and functions */

__attribute__((used)) static inline void __btree_init(struct btree_head *head)
{
	head->node = NULL;
	head->height = 0;
}