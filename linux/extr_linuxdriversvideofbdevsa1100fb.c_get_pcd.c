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
struct sa1100fb_info {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int get_pcd(struct sa1100fb_info *fbi,
		unsigned int pixclock)
{
	unsigned int pcd = clk_get_rate(fbi->clk) / 100 / 1000;

	pcd *= pixclock;
	pcd /= 10000000;

	return pcd + 1;	/* make up for integer math truncations */
}