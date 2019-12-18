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
struct RavlNode {struct RavlNode* right; struct RavlNode* left; int /*<<< orphan*/  ip_end; int /*<<< orphan*/  ip_begin; } ;
typedef  int /*<<< orphan*/  (* RAVL_CALLBACK ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */

void
ravl_enumerate(struct RavlNode *node, RAVL_CALLBACK callback_func, void *callback_data)
{
    if (node == NULL)
        return;

    callback_func(callback_data, node->ip_begin, node->ip_end);

    ravl_enumerate(node->left, callback_func, callback_data);
    ravl_enumerate(node->right, callback_func, callback_data);
}