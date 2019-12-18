#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ node; scalar_t__ off; } ;
typedef  TYPE_1__ rangepoint_t ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL rangepoint_cmp(const rangepoint_t *point1, const rangepoint_t *point2)
{
    return point1->node == point2->node && point1->off == point2->off;
}