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

/* Variables and functions */
 int /*<<< orphan*/  newport_clear_screen (int /*<<< orphan*/ ,int,int,int,int) ; 
 int topscan ; 

__attribute__((used)) static inline void newport_clear_lines(int ystart, int yend, int ci)
{
	ystart = ((ystart << 4) + topscan) & 0x3ff;
	yend = ((yend << 4) + topscan + 15) & 0x3ff;
	newport_clear_screen(0, ystart, 1280 + 63, yend, ci);
}