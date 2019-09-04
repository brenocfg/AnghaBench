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
typedef  int /*<<< orphan*/  tree ;
struct cgraph_node {int dummy; } ;

/* Variables and functions */
 struct cgraph_node* cgraph_get_node (int /*<<< orphan*/ ) ; 
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cgraph_node *cgraph_get_create_node(tree decl)
{
	struct cgraph_node *node = cgraph_get_node(decl);

	return node ? node : cgraph_node(decl);
}