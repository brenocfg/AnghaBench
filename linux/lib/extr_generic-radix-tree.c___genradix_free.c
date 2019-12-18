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
struct genradix_root {int dummy; } ;
struct __genradix {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  genradix_free_recurse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genradix_root_to_depth (struct genradix_root*) ; 
 int /*<<< orphan*/  genradix_root_to_node (struct genradix_root*) ; 
 struct genradix_root* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void __genradix_free(struct __genradix *radix)
{
	struct genradix_root *r = xchg(&radix->root, NULL);

	genradix_free_recurse(genradix_root_to_node(r),
			      genradix_root_to_depth(r));
}