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
struct RavlNode {void* height; struct RavlNode* left; struct RavlNode* right; } ;

/* Variables and functions */
 void* height (struct RavlNode*) ; 
 void* max (void*,void*) ; 

__attribute__((used)) static struct RavlNode *
single_rotate_with_left(struct RavlNode* k2)
{
    struct RavlNode* k1 = NULL;
 
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
 
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1U;
    k1->height = max( height( k1->left ), k2->height ) + 1U;
    return k1; /* new root */
}