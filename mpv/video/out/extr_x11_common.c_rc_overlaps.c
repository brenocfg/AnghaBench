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
struct mp_rect {int dummy; } ;

/* Variables and functions */
 int mp_rect_intersection (struct mp_rect*,struct mp_rect*) ; 

__attribute__((used)) static bool rc_overlaps(struct mp_rect rc1, struct mp_rect rc2)
{
    return mp_rect_intersection(&rc1, &rc2); // changes the first argument
}