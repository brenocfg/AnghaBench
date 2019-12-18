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
typedef  int /*<<< orphan*/  xa_mark_t ;
struct xa_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  node_marks (struct xa_node*,int /*<<< orphan*/ ) ; 
 int test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool node_get_mark(struct xa_node *node,
		unsigned int offset, xa_mark_t mark)
{
	return test_bit(offset, node_marks(node, mark));
}