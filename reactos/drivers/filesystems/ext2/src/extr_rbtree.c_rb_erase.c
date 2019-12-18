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
struct rb_root {struct rb_node* rb_node; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; int /*<<< orphan*/  rb_parent_color; } ;
typedef  scalar_t__ ULONG_PTR ;

/* Variables and functions */
 scalar_t__ RB_BLACK ; 
 int /*<<< orphan*/  __rb_erase_color (struct rb_node*,struct rb_node*,struct rb_root*) ; 
 scalar_t__ rb_color (struct rb_node*) ; 
 struct rb_node* rb_parent (struct rb_node*) ; 
 int /*<<< orphan*/  rb_set_parent (struct rb_node*,struct rb_node*) ; 

void rb_erase(struct rb_node *node, struct rb_root *root)
{
    struct rb_node *child, *parent;
    ULONG_PTR color;

    if (!node->rb_left)
        child = node->rb_right;
    else if (!node->rb_right)
        child = node->rb_left;
    else
    {
        struct rb_node *old = node, *left;

        node = node->rb_right;
        while ((left = node->rb_left) != NULL)
            node = left;
        child = node->rb_right;
        parent = rb_parent(node);
        color = rb_color(node);

        if (child)
            rb_set_parent(child, parent);
        if (parent == old) {
            parent->rb_right = child;
            parent = node;
        } else
            parent->rb_left = child;

        node->rb_parent_color = old->rb_parent_color;
        node->rb_right = old->rb_right;
        node->rb_left = old->rb_left;

        if (rb_parent(old))
        {
            if (rb_parent(old)->rb_left == old)
                rb_parent(old)->rb_left = node;
            else
                rb_parent(old)->rb_right = node;
        } else
            root->rb_node = node;

        rb_set_parent(old->rb_left, node);
        if (old->rb_right)
            rb_set_parent(old->rb_right, node);
        goto color;
    }

    parent = rb_parent(node);
    color = rb_color(node);

    if (child)
        rb_set_parent(child, parent);
    if (parent)
    {
        if (parent->rb_left == node)
            parent->rb_left = child;
        else
            parent->rb_right = child;
    }
    else
        root->rb_node = child;

color:
    if (color == RB_BLACK)
        __rb_erase_color(child, parent, root);
}