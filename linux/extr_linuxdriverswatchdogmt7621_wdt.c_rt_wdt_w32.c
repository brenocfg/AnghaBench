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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int mt7621_wdt_base ; 

__attribute__((used)) static inline void rt_wdt_w32(unsigned reg, u32 val)
{
	iowrite32(val, mt7621_wdt_base + reg);
}