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
struct mpv_node {scalar_t__ format; int /*<<< orphan*/  u; } ;

/* Variables and functions */
 int equal_mpv_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

bool equal_mpv_node(const struct mpv_node *a, const struct mpv_node *b)
{
    if (a->format != b->format)
        return false;
    return equal_mpv_value(&a->u, &b->u, a->format);
}