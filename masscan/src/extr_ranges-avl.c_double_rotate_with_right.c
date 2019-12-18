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
struct RavlNode {int /*<<< orphan*/  right; } ;

/* Variables and functions */
 int /*<<< orphan*/  single_rotate_with_left (int /*<<< orphan*/ ) ; 
 struct RavlNode* single_rotate_with_right (struct RavlNode*) ; 

__attribute__((used)) static struct RavlNode *
double_rotate_with_right( struct RavlNode* k1 )
{
    /* rotate between K3 and k2 */
    k1->right = single_rotate_with_left(k1->right);
 
    /* rotate between k1 and k2 */
    return single_rotate_with_right(k1);
}