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
struct text_leaf {struct text_leaf* value; struct text_leaf* lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct text_leaf*) ; 

__attribute__((used)) static inline void text_leaf_destroy(struct text_leaf *leaf)
{
	if (leaf) {
		bfree(leaf->lookup);
		bfree(leaf->value);
		bfree(leaf);
	}
}