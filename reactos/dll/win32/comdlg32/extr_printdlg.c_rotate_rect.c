#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* bottom; void* right; void* top; void* left; } ;
typedef  TYPE_1__ RECT ;
typedef  void* INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

__attribute__((used)) static inline void rotate_rect(RECT *rc, BOOL sense)
{
    INT tmp;
    if(sense)
    {
        tmp        = rc->bottom;
        rc->bottom = rc->right;
        rc->right  = rc->top;
        rc->top    = rc->left;
        rc->left   = tmp;
    }
    else
    {
        tmp        = rc->left;
        rc->left   = rc->top;
        rc->top    = rc->right;
        rc->right  = rc->bottom;
        rc->bottom = tmp;
    }
}