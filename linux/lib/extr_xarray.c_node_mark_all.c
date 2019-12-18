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
 int /*<<< orphan*/  XA_CHUNK_SIZE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_marks (struct xa_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void node_mark_all(struct xa_node *node, xa_mark_t mark)
{
	bitmap_fill(node_marks(node, mark), XA_CHUNK_SIZE);
}