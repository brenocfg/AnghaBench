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
struct edge_node {int flags; struct bb_node* dst; struct bb_node* src; } ;
struct bb_node {int dummy; } ;

/* Variables and functions */
 struct edge_node* calloc (int,int) ; 
 int /*<<< orphan*/  p_err (char*) ; 

__attribute__((used)) static struct edge_node *new_edge(struct bb_node *src, struct bb_node *dst,
				  int flags)
{
	struct edge_node *e;

	e = calloc(1, sizeof(*e));
	if (!e) {
		p_err("OOM when allocating edge node");
		return NULL;
	}

	if (src)
		e->src = src;
	if (dst)
		e->dst = dst;

	e->flags |= flags;

	return e;
}