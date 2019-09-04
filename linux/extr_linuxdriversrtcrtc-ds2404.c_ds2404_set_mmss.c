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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 int /*<<< orphan*/  ds2404_write_memory (struct device*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds2404_set_mmss(struct device *dev, unsigned long secs)
{
	u32 time = cpu_to_le32(secs);
	ds2404_write_memory(dev, 0x203, 4, (u8 *)&time);
	return 0;
}