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
struct xa_state {int /*<<< orphan*/  xa_offset; int /*<<< orphan*/  xa_node; int /*<<< orphan*/  xa; } ;

/* Variables and functions */
 int node_get_mark (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xa_marked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xas_invalid (struct xa_state const*) ; 

bool xas_get_mark(const struct xa_state *xas, xa_mark_t mark)
{
	if (xas_invalid(xas))
		return false;
	if (!xas->xa_node)
		return xa_marked(xas->xa, mark);
	return node_get_mark(xas->xa_node, xas->xa_offset, mark);
}