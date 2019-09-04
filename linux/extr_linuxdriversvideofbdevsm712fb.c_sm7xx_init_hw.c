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
 int /*<<< orphan*/  outb_p (int,int) ; 

__attribute__((used)) static inline void sm7xx_init_hw(void)
{
	outb_p(0x18, 0x3c4);
	outb_p(0x11, 0x3c5);
}