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
struct bitmask {int dummy; } ;

/* Variables and functions */
 unsigned int bitmask_next (struct bitmask const*,int /*<<< orphan*/ ) ; 

unsigned int bitmask_first(const struct bitmask *bmp)
{
	return bitmask_next(bmp, 0);
}